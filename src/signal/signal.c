/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:15:27 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/18 13:15:32 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sig_c(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_nl(int sig)
{
	if (sig == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	else if (sig == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", 2);
}

void	init_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, sig_c);
}
