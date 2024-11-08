/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/11/04 16:30:05 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/04 16:43:23 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


// Malloc + initilise a 0 la structure global
void	calloc_global_struct(t_global **global_data)
{
	*global_data = ft_calloc(1, sizeof(t_global));
	if (!*global_data)
		return (perror("error, global struct calloc failed"));
}

char	**fill_arg_after_cmd(t_token *token_list)
{
	t_token *current_token;
	char **cmd_args;
	int nbr_arg;
	int i;

	// int y;
	i = -1;
	current_token = token_list;
	nbr_arg = nbr_arg_after_cmd(token_list);
	cmd_args = malloc((nbr_arg + 1) * sizeof(char *));
	if (!cmd_args)
	{
		free(cmd_args);
		return (perror("error, malloc failed"), NULL);
	}
	current_token = current_token->next;
	while (++i < nbr_arg && current_token && current_token->type == ARG)
	{
		cmd_args[i] = ft_strdup(current_token->token);
		if (!cmd_args[i])
		{
			free_array(cmd_args);
			return (perror("error, malloc failed"), NULL);
		}
		current_token = current_token->next;
	}
	cmd_args[i] = NULL;
	/// TESTS A ENLEVER PLUS TARD ///////////////////////////////
	// y = 0;
	// while (cmd_args[y])
	// {
	// 	printf("cmd_arg : %s\n", cmd_args[y]);
	// 	y++;
	// }
	////////////////////////////////////////////////////////////
	return (cmd_args);
}

void	init_env_list(t_env **env_to_add, char **env)
{
	int i;

	i = 0;
	// init_env(env_to_add);
	if (!env || !*env)
		return (perror("error, empty env list"));
	while (env[i])
	{
		env_add_node(env_to_add, env[i]);
		i++;
	}
}

// void	init_env(t_env **env)
// {
// 	env->value = ft_strch_env_value(ft_strchr(env->env, '='));
// 	env->name = ft_strchr_env_name(env->name, env->env);
// }
