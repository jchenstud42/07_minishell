/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:26:02 by jchen             #+#    #+#             */
/*   Updated: 2024/12/14 19:02:02 by jchen            ###   ########.fr       */
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

static void	launch_redirection(t_global *global, t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->infile_cmd == INPUT || tmp->infile_cmd == HEREDOC
			|| tmp->outfile_cmd == APPEND || tmp->outfile_cmd == OUTPUT)
			handle_redirection(global, cmd);
		tmp = tmp->next;
	}
}

void	launch_line(t_global *global, t_env **env)
{
	t_cmd	*current_cmd;

	if (!global)
		return (perror("erreur, empty global struct"));
	launch_redirection(global, global->cmd_list);
	if (!global->cmd_list->cmd)
		return ;
	current_cmd = (global->cmd_list);
	if (pipe_inside_token_list(global))
		execute_pipe(current_cmd, global);
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

// void	launch_redirection(t_global *global, t_token *token)
// {
// 	t_token	*tmp;

// 	tmp = token;
// 	while (tmp)
// 	{
// 		if (tmp->type == INPUT || tmp->type == HEREDOC || tmp->type == APPEND
// 			|| tmp->type == OUTPUT)
// 			handle_redirection(global, token);
// 		tmp = tmp->next;
// 	}
// }

// void	launch_line(t_global *global, t_env **env, t_token *token_list)
// {
// 	t_cmd	*current_cmd;

// 	if (!global)
// 		return (perror("erreur, empty global struct"));
// 	launch_redirection(global, token_list);
// 	if (!global->cmd_list->cmd)
// 		return ;
// 	current_cmd = (global->cmd_list);
// 	if (pipe_inside_token_list(global))
// 		execute_pipe(current_cmd, global);
// 	else
// 	{
// 		while (current_cmd)
// 		{
// 			if (is_builtin(current_cmd->cmd) == 0)
// 				execute_builtin(current_cmd, global);
// 			else
// 				execute_command(global, current_cmd, env);
// 			current_cmd = current_cmd->next;
// 		}
// 	}
// }
