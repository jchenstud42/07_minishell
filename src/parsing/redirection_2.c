/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:27:09 by rbouquet          #+#    #+#             */
/*   Updated: 2024/12/16 18:30:12 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	redirect_trunc_append(t_cmd *cmd, char *filename, t_global *global,
		int mode)
{
	int	fd;

	fd = open(filename, mode, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell:", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
		cmd->infile = -2;
		global->exit_value = 1;
		return (1);
	}
	cmd->outfile = fd;
	global->exit_value = 0;
	return (0);
}

static int	redirect_input(t_cmd *cmd, char *filename, t_global *global,
		int mode)
{
	int	fd;

	fd = open(filename, mode, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell:", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
		cmd->infile = -2;
		global->exit_value = 1;
		return (1);
	}
	cmd->infile = fd;
	global->exit_value = 0;
	return (0);
}

int	handle_redirection(t_global *global, t_cmd *cmd)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
		return (perror("dup sauvegarde"), 1);
	while (cmd)
	{
		if (cmd->infile == INPUT)
			redirect_input(cmd, cmd->filename, global, O_RDONLY);
		else if (cmd->infile == HEREDOC)
			ft_heredoc(global, cmd->filename, cmd);
		else if (cmd->outfile == OUTPUT)
			redirect_trunc_append(cmd, cmd->filename, global,
				O_WRONLY | O_TRUNC | O_CREAT);
		else if (cmd->outfile == APPEND)
			redirect_trunc_append(cmd, cmd->filename, global,
				O_WRONLY | O_APPEND | O_CREAT);
		cmd = cmd->next;
	}
	if (dup2(saved_stdin, STDIN_FILENO) == -1 || dup2(saved_stdout,
			STDOUT_FILENO) == -1)
		perror("Restauration stdout/stdin");
	return (close(saved_stdin), close(saved_stdout));
}
