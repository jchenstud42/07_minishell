/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:41:01 by jchen             #+#    #+#             */
/*   Updated: 2024/12/01 18:45:45 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// WIFEXITED : retoune vrai si le child s'est terminé normalement
// WIFEXITSATUS : code de sortie du processus
// WIFSIGNALED : retourne vrai si un signal a causé la terminaison
// WTERMSIG :renvoie le numero du signal qui a cause la terminaison
void	status_child(t_global *global, pid_t pid)
{
	int	signal;

	signal = WTERMSIG(pid);
	if (WIFEXITED(pid))
		global->exit_value = WEXITSTATUS(pid);
	else if (WIFSIGNALED(pid))
	{
		if (signal == SIGPIPE)
			global->exit_value = 0;
		else
		{
			global->exit_value = WTERMSIG(pid);
			if (global->exit_value != 131)
				global->exit_value = WTERMSIG(pid) + 128;
		}
	}
}

void	catch_signals(t_global *global)
{
	int	status;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_nl);
	signal(SIGQUIT, handle_nl);
	while (wait(&status) > 0)
		;
	status_child(global, status);
	signal(SIGINT, SIG_DFL);
}
