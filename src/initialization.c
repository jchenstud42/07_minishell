/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:23:16 by rbouquet          #+#    #+#             */
/*   Updated: 2024/12/18 09:23:19 by rbouquet         ###   ########.fr       */
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
	t_token	*current_token;
	char	**cmd_args;
	int		nbr_arg;
	int		i;

	i = -1;
	current_token = token_list;
	nbr_arg = nbr_arg_after_cmd(token_list);
	cmd_args = malloc((nbr_arg + 1) * sizeof(char *));
	if (!cmd_args)
		return (free(cmd_args), perror("error, malloc failed"), NULL);
	current_token = current_token->next;
	while (++i < nbr_arg && current_token && current_token->type == ARG)
	{
		cmd_args[i] = ft_strdup(current_token->token);
		if (!cmd_args[i])
			return (free_array(cmd_args), perror("malloc failed"), NULL);
		current_token = current_token->next;
	}
	cmd_args[i] = NULL;
	return (cmd_args);
}

void	init_env_list(t_env **env_to_add, char **env)
{
	int	i;

	i = 0;
	if (!env || !*env)
		return (perror("error, empty env list"));
	while (env[i])
	{
		env_add_node(env_to_add, env[i]);
		i++;
	}
}

void	init_env(t_env *env_list)
{
	char	*value;

	env_list->name = NULL;
	env_list->value = NULL;
	env_list->name = ft_strchr_env_name(env_list->name, env_list->env);
	if (env_list->name == NULL)
		return ;
	value = ft_strchr(env_list->env, '=');
	if (value)
	{
		env_list->value = ft_strdup(value + 1);
		if (env_list->value == NULL)
		{
			free(env_list->name);
			env_list->name = NULL;
			return ;
		}
	}
}
