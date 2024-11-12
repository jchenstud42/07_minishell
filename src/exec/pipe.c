/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/11/08 15:44:41 by jchen             #+#    #+#             */
/*   Updated: 2024/11/08 15:44:41 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


// Permet de dupliquer, rediriger et fermer les descripteurs de fichier.
void	handle_redirections(t_cmd *cmd, int input_fd, int *fds)
{
	if (input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
			exit(1);
		close(input_fd);
	}
	if (cmd->next)
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			exit(1);
		close(fds[1]);
	}
	close(fds[0]);
	if (cmd->infile != -1)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			exit(1);
		close(cmd->infile);
	}
	if (cmd->outfile != -1)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
			exit(1);
		close(cmd->outfile);
	}
}

// Processus parent
void	parent_process(int *fds, int *input_fd, pid_t pid)
{
	(void)pid;
	close(fds[1]);
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	*input_fd = fds[0];
}

// Processus enfant
void	child_process(t_cmd *cmd, int *fds, t_global *global, char **env,
		int input_fd)
{
	char *command_path;

	command_path = get_command_path(cmd->cmd);
	handle_redirections(cmd, input_fd, fds);
	signal(SIGINT, SIG_DFL);
	if (is_builtin(cmd->cmd_args[0]) == 0)
	{
		execute_builtin(cmd, global);
		exit(0);
	}
	if (!access(cmd->cmd, X_OK))
		execve(cmd->cmd, cmd->cmd_args, env);
	execve(command_path, cmd->cmd_args, env);
	free(command_path);
	slash_in_cmd_token(cmd->cmd, true);
	exit(1);
}

// Simule l'execution des pipes.
void	execute_pipe(t_cmd *cmd, char **env, t_global *global)
{
	int fds[2];
	pid_t pid;
	int input_fd;

	input_fd = STDIN_FILENO;
	while (cmd)
	{
		if (cmd->next && pipe(fds) == -1)
			exit(1);
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
			child_process(cmd, fds, global, env, input_fd);
		else
			parent_process(fds, &input_fd, pid);
		cmd = cmd->next;
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_nl);
	signal(SIGQUIT, handle_nl);
	while (wait(NULL) > 0)
		;
	signal(SIGINT, SIG_DFL);
}
