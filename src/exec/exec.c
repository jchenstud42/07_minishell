/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:09:49 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/28 15:19:53 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Interprete et lance le prompt
void	launch_line(t_global *global, char **env)
{
	if (!global)
		return ;
	while (global->token_list)
	{
		if (global->token_list->type == CMD)
			execute_command(global->token_list->token, env, global);
		global->token_list = global->token_list->next;
	}
}
