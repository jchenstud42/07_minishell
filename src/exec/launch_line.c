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

void	launch_redirection(t_global *global, t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == INPUT || tmp->type == HEREDOC || tmp->type == TRUNC
			|| tmp->type == APPEND)
			handle_redirection(global, token);
		tmp = tmp->next;
	}
}

void	launch_line(t_global *global, t_env **env, t_token *token_list)
{
	t_cmd	*current_cmd;

	if (!global)
		return (perror("erreur, empty global struct"));
	launch_redirection(global, token_list);
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

// void	launch_line(t_global *global, t_env **env, t_token *token_list)
// {
// 	t_cmd	*current_cmd;
// 	t_token	*tmp;

// 	tmp = token_list;
// 	if (!global)
// 		return (perror("erreur, empty global struct"));
// 	current_cmd = (global->cmd_list);
// 	while (tmp)
// 	{
// 		if (tmp->type == INPUT || tmp->type == HEREDOC || tmp->type == TRUNC
// 			|| tmp->type == APPEND)
// 			handle_redirection(global, global->token_list);
// 		tmp = tmp->next;
// 	}
// 	if (pipe_inside_token_list(global))
// 		execute_pipe(current_cmd, global);
// 	else
// 	{
// 		while (current_cmd)
// 		{
// 			if (is_builtin(current_cmd->cmd) == 0)
// 				execute_builtin(current_cmd, global);
// 			else
// 				execute_command(global, current_cmd, env, token_list);
// 			current_cmd = current_cmd->next;
// 		}
// 	}
// }

// ANCIEN ANCIEN ANCIEN

// Interprete et lance le prompt
// void	launch_line(t_global *global, t_env **env, t_token *token_list)
// {
// 	t_cmd	*current_cmd;

// 	if (!global)
// 		return (perror("erreur, empty global struct"));
// 	current_cmd = (global->cmd_list);
// 	if (pipe_inside_token_list(global))
// 		execute_pipe(current_cmd, global);
// 	else if (token_list->type == INPUT || token_list->type == HEREDOC
// 		|| token_list->type == TRUNC || token_list->type == APPEND)
// 		handle_redirection(global, global->token_list);
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
