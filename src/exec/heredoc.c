/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:57:21 by jchen             #+#    #+#             */
/*   Updated: 2024/12/14 19:04:19 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	in_heredoc(int fd, char *word)
{
	char	*heredoc;

	while (1)
	{
		heredoc = readline("> ");
		if (!heredoc)
		{
			write(2, "minishell: warning: here-document delimited by ", 47);
			write(2, "end-of-file (wanted '", 21);
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
	return (true);
}

static void	sigint_in_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = sig_heredoc;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (perror("sigaction failed\n"));
}

static void	child_heredoc(int *fd, char *word)
{
	sigint_in_heredoc();
	if (!in_heredoc(*fd, word))
	{
		close(*fd);
		unlink(".heredoc.tmp");
		return ;
	}
	*fd = open(".heredoc.tmp", O_RDONLY);
	if (*fd > 0)
		unlink(".heredoc.tmp");
	close(*fd);
}

int	ft_heredoc(t_global *global, char *word, t_cmd *cmd)
{
	int		fd;
	pid_t	pid;
	int		status;

	cmd->infile_cmd = -1;
	fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	pid = fork();
	if (pid == -1)
		return (close(fd), perror("error, fork failed"), 1);
	else if (pid == 0)
	{
		child_heredoc(&fd, word);
		exit(0);
	}
	else
	{
		signal(SIGINT, handle_nl);
		waitpid(pid, &status, 0);
		if (WEXITSTATUS(status) == 130 || WEXITSTATUS(status) == 0)
			return (close(fd), unlink(".heredoc.tmp"),
				global->exit_value = WEXITSTATUS(status), 1);
	}
	return (fd);
}
