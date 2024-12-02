/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:30:37 by jchen             #+#    #+#             */
/*   Updated: 2024/12/02 16:55:21 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_heredoc(t_global *global, int fd, char *word)
{
	char	*heredoc;

	while (1)
	{
		heredoc = readline("> ");
		if (!heredoc)
		{
			write(2, "warning: here-document delimited by end-of-file ", 48);
			write(2, "(wanted '", 9);
			write(2, word, ft_strlen(word));
			write(2, "')\n", 3);
			break ;
		}
		if (ft_strcmp(heredoc, word) == 0)
		{
			free(heredoc);
			break ;
		}
		write(fd, heredoc, ft_strlen(heredoc));
		write(fd, "\n", 1);
		free(heredoc);
	}
	close(fd);
	global->exit_value = 0;
	return (true);
}

int	in_heredoc(t_global *global, char *word)
{
	int	fd;

	fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	if (!ft_heredoc(global, fd, word))
	{
		unlink(".heredoc.tmp");
		return (1);
	}
	fd = open(".heredoc.tmp", O_RDONLY);
	if (fd > 0)
		unlink(".heredoc.tmp");
	return (fd);
}
