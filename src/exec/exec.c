/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:09:49 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/07 15:20:39 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Verifie s'il y a un token de type PIPE dans notre liste
bool	pipe_inside_token_list(t_global *global)
{
	t_token	*temp;

	if (!global | !global->token_list)
		return (false);
	temp = global->token_list;
	while (temp)
	{
		if (temp->type == PIPE)
			return (true);
		temp = temp->next;
	}
	return (false);
}

// Remplie un double tableau de string d'arguments
// qui seront utilises par execve()
void	fill_cmd_double_array(t_token *token_list, t_cmd *cmd_list)
{
	t_token	*current_token;
	int		i;

	if (!token_list || !cmd_list)
		return (perror("error, empty array"));
	i = -1;
	current_token = token_list;
	while (current_token)
	{
		if (current_token->type == CMD)
			cmd_list->cmd_arrays[++i] = fill_execve_arg_array(current_token);
		current_token = current_token->next;
	}
}

// Interprete et lance le prompt
void	launch_line(t_global *global, char **env)
{
	if (!global)
		return (perror("erreur, empty global struct"));
	if (pipe_inside_token_list(global))
	{
		init_cmd_double_array(global);
		fill_cmd_double_array(global->token_list, global->cmd_list);
		execute_pipe(global->cmd_list->cmd_arrays, env, global);
	}
	else
	{
		while (global->token_list)
		{
			if (global->token_list->type == CMD)
			{
				if (is_builtin(global->token_list->token) == 0)
					execute_builtin(global->token_list->token, global);
				else
					execute_command(global->token_list->token, env, global);
			}
			global->token_list = global->token_list->next;
		}
	}
}
