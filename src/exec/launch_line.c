/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
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

// Interprete et lance le prompt
void	launch_line(t_global *global, t_env **env, t_token *token_list)
{
	t_cmd	*current_cmd;

	if (!global)
		return (perror("erreur, empty global struct"));
	current_cmd = (global->cmd_list);
	if (pipe_inside_token_list(global))
		execute_pipe(current_cmd, global);
	else if (token_list->type == HEREDOC)
		in_heredoc(global, &token_list->next->token[0]);
	else
	{
		while (current_cmd)
		{
			if (is_builtin(current_cmd->cmd) == 0)
				execute_builtin(current_cmd, global);
			else
				execute_command(global, current_cmd, env);
			current_cmd = current_cmd->next;
		}
	}
}
