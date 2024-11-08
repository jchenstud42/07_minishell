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
	(*global_data)->line = NULL;
	(*global_data)->token_list = NULL;
}

// Initialise notre tableau de tableau de commandes (char ***)
void	init_cmd_double_array(t_global *global)
{
	int	nbr_cmd;

	global->cmd_list = ft_calloc(1, sizeof(t_cmd));
	if (!global || !global->cmd_list)
	{
		perror("error, struct not initialized");
		return ;
	}
	nbr_cmd = count_cmd_token(global->token_list);
	global->cmd_list->cmd_arrays = ft_calloc((nbr_cmd + 1), sizeof(char **));
	if (!global->cmd_list->cmd_arrays)
		return (perror("error, double array malloc failed"));
}

char	**fill_arg_after_cmd(t_token *token_list)
{
	t_token	*current_token;
	char	**execve_args;
	int		nbr_arg;
	int		i;

	// int		y;
	i = -1;
	current_token = token_list;
	nbr_arg = nbr_arg_after_cmd(token_list);
	execve_args = malloc((nbr_arg + 1) * sizeof(char *));
	if (!execve_args)
	{
		free(execve_args);
		return (perror("error, malloc failed"), NULL);
	}
	current_token = current_token->next;
	while (++i < nbr_arg && current_token && current_token->type == ARG)
	{
		execve_args[i] = ft_strdup(current_token->token);
		if (!execve_args[i])
		{
			free_array(execve_args);
			return (perror("error, malloc failed"), NULL);
		}
		current_token = current_token->next;
	}
	execve_args[i] = NULL;
	/// TESTS A ENLEVER PLUS TARD ///////////////////////////////
	// y = 0;
	// while (execve_args[y])
	// {
	// 	printf("%s\n", execve_args[y]);
	// 	y++;
	// }
	////////////////////////////////////////////////////////////
	return (execve_args);
}

void	init_env_list(t_env **env_to_add, char **env)
{
	int	i;

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
