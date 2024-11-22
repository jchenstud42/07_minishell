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

// WIFSIGNALED : retourne vrai si un signal a causé la terminaison
// WTERMSIG :renvoie le numero du signal qui a cause la terminaison
// WIFEXITED : retoune vrai si le child s'est terminé normalement
// WIFEXITSATUS : code de sortie du processus
void	status_child(t_global *global, pid_t pid)
{
	// int	signal;

	// signal = WTERMSIG(pid);
	if (WIFEXITED(pid))
		global->exit_value = WEXITSTATUS(pid);
	else if (WIFSIGNALED(pid))
	{
		// if (signal == SIGPIPE)
		// 	global->exit_value = 666;
		// else
		// global->exit_value = WTERMSIG(pid) + 128;
		global->exit_value = WTERMSIG(pid);
	}
}

static void	execute_command_in_pipe(t_cmd *cmd_list, t_env **env,
		t_global *global)
{
	char	**env_cpy;

	env_cpy = get_env(*env);
	if (!cmd_list->cmd)
		exit(1);
	if (!access(cmd_list->cmd, X_OK))
		execve(cmd_list->cmd, cmd_list->cmd_args, env_cpy);
	cmd_list->cmd_path = get_command_path(cmd_list->cmd);
	if ((execve(cmd_list->cmd_path, cmd_list->cmd_args, env_cpy) == -1)
		&& !slash_in_cmd_token(cmd_list->cmd, true))
	{
		ft_putstr_fd(cmd_list->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		// free_array(env_cpy);
		free_all(global);
		exit(127);
	}
	exit(1);
}

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
	if (cmd->infile_cmd != -1)
	{
		if (dup2(cmd->infile_cmd, STDIN_FILENO) == -1)
			exit(1);
		close(cmd->infile_cmd);
	}
	if (cmd->outfile_cmd != -1)
	{
		if (dup2(cmd->outfile_cmd, STDOUT_FILENO) == -1)
			exit(1);
		close(cmd->outfile_cmd);
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
void	child_process(t_cmd *cmd, int *fds, t_global *global, int input_fd)
{
	signal(SIGQUIT, SIG_DFL);
	handle_redirections(cmd, input_fd, fds);
	if (is_builtin(cmd->cmd_args[0]) == 0)
	{
		execute_builtin(cmd, global);
		exit(0);
	}
	execute_command_in_pipe(cmd, &global->env_list, global);
}

// Simule l'execution des pipes.
void	execute_pipe(t_cmd *cmd, t_global *global)
{
	int		fds[2];
	pid_t	pid;
	int		input_fd;
	int		status;

	input_fd = STDIN_FILENO;
	while (cmd)
	{
		if (cmd->next && pipe(fds) == -1)
			exit(1);
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
			child_process(cmd, fds, global, input_fd);
		else
			parent_process(fds, &input_fd, pid);
		cmd = cmd->next;
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_nl);
	signal(SIGQUIT, handle_nl);
	while (wait(&status) > 0)
		;
	status_child(global, status);
	signal(SIGINT, SIG_DFL);
}
