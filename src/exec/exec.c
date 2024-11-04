/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:09:49 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/04 12:36:02 by rbouquet         ###   ########.fr       */
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
		return ;
	if (pipe_inside_token_list(global))
		execute_pipe(global->line, env, global);
	else
		while (global->token_list)
		{
			if (global->token_list->type == CMD)
				if (is_builtin(global->token_list->type))
					return ()
				execute_command(global->token_list->token, env, global);
			global->token_list = global->token_list->next;
		}
}
