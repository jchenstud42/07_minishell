/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:09:52 by jchen             #+#    #+#             */
/*   Updated: 2024/12/18 11:46:20 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	execute_command_in_pipe(t_cmd *cmd_list, t_env **env,
		t_global *global)
{
	if (global->env_array)
		free_array(global->env_array);
	global->env_array = get_env(*env);
	if (!check_valid_type(global->token_list, cmd_list)
		|| !check_env_path_exists(global, global->env_array, cmd_list))
		free_all(global);
	if (!access(cmd_list->cmd, X_OK))
		execve(cmd_list->cmd, cmd_list->cmd_args, global->env_array);
	cmd_list->cmd_path = get_command_path(cmd_list->cmd);
	global->exit_value = 0;
	if (!cmd_list->cmd_path || ((execve(cmd_list->cmd_path, cmd_list->cmd_args,
					global->env_array) == -1)
			&& !slash_in_cmd_token(cmd_list->cmd, true)))
	{
		ft_putstr_fd(cmd_list->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		global->exit_value = 127;
		free_all(global);
	}
}

// Permet de dupliquer, rediriger et fermer les descripteurs de fichier.
void	handle_redirections_pipe(t_cmd *cmd, int input_fd, int *fds)
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
	if (cmd->infile > -1)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			exit(1);
		close(cmd->infile);
	}
	if (cmd->outfile > -1)
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
void	child_process(t_cmd *cmd, int *fds, t_global *global, int input_fd)
{
	signal(SIGQUIT, SIG_DFL);
	handle_redirections_pipe(cmd, input_fd, fds);
	if (is_builtin(cmd->cmd_args[0]) == 0)
	{
		prepare_builtin(cmd, global);
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
	catch_signals(global);
}
