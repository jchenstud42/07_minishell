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
void	launch_line(t_global *global, char **env)
{
	if (!global)
		return (perror("erreur, empty global struct"));
	if (pipe_inside_token_list(global))
		execute_pipe(global->cmd_list, env, global);
	else
	{
		while (global->cmd_list)
		{
			if (is_builtin(global->cmd_list->cmd) == 0)
				execute_builtin(global->cmd_list, global);
			else
				execute_command(global->cmd_list, env);
			global->cmd_list = global->cmd_list->next;
		}
	}
}
