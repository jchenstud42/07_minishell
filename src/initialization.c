/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
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
		error_handler(STRUCT_INIT_FAILED, *global_data);
	(*global_data)->line = NULL;
	(*global_data)->token_list = NULL;
}

// Initialise notre tableau de tableau de commandes (char ***)
char	***init_cmd_double_array(t_global *global)
{
	int		nbr_cmd;
	char	***cmd_arrays;

	if (!global)
		error_handler(STRUCT_NOT_INITIALIZED, global);
	nbr_cmd = count_cmd_token(global->token_list);
	cmd_arrays = ft_calloc((nbr_cmd + 1), sizeof(char **));
	if (!cmd_arrays)
	{
		free(cmd_arrays);
		error_handler(MALLOC_FAILED, global);
	}
	return (cmd_arrays);
}

char	**fill_arg_after_cmd(t_global *global, t_token *token_list)
{
	t_token	*current_token;
	char	**execve_args;
	int		nbr_arg;
	int		i;

	i = -1;
	current_token = token_list;
	nbr_arg = nbr_arg_after_cmd(token_list);
	execve_args = malloc((nbr_arg + 1) * sizeof(char *));
	if (!execve_args)
	{
		free(execve_args);
		error_handler(MALLOC_FAILED, global);
	}
	current_token = current_token->next;
	while (++i < nbr_arg && current_token)
	{
		execve_args[i] = ft_strdup(current_token->token);
		if (!execve_args[i])
		{
			free_array(execve_args);
			error_handler(MALLOC_FAILED, global);
		}
		current_token = current_token->next;
	}
	execve_args[i] = NULL;
	return (execve_args);
}

int	nbr_arg_after_cmd2(t_token *token_list)
{
	int		nbr_arg;
	t_token	*current_token;

	nbr_arg = 0;
	if (!token_list)
		return (-1);
	current_token = token_list->next;
	while (current_token && current_token->type == ARG)
	{
		current_token = current_token->next;
		nbr_arg++;
	}
	return (nbr_arg);
}

void	init_env(t_env **env_to_add, char **env)
{
	int	i;

	i = 0;
	if (!env || !*env)
		return ;
	while (env[i])
	{
		env_add_node(env_to_add, env[i]);
		i++;
	}
}
