/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:17:35 by jchen             #+#    #+#             */
/*   Updated: 2024/11/08 10:45:36 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_redirections(int backup_fd, int *fds, char ***cmd,
		t_global *global)
{
	(void)*global;
	if (backup_fd != STDIN_FILENO)
	{
		if (dup2(backup_fd, STDIN_FILENO) == -1)
			exit(1);
		close(backup_fd);
	}
	if (*(cmd + 1))
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			exit(1);
	}
	close(fds[0]);
	if (global->cmd_list->cmd_number != 0)
	{
		if (dup2(1, STDIN_FILENO) == -1)
			exit(1);
		close(1);
	}
	if (global->cmd_list->cmd_number != 1)
	{
		if (dup2(0, STDOUT_FILENO) == -1)
			exit(1);
		close(0);
	}
	global->cmd_list->cmd_number++;
}

// Processus enfant
// void	child_process(char ***cmd, int *fds, t_global *global, char **env,
// 		int backup_fd)
// {
// 	if (dup2(backup_fd, STDOUT_FILENO) == -1)
// 		return (perror("error, dup failed"));
// 	handle_redirections(backup_fd, fds, cmd, global);
// 	close(fds[1]);
// 	if (is_builtin((*cmd)[0]) == 0)
// 	{
// 		execute_builtin((*cmd)[0], global);
// 		exit(0);
// 	}
// 	global->cmd_list->cmd_path = get_command_path((*cmd)[0]);
// 	execve(global->cmd_list->cmd_path, *cmd, env);
// }

void	child_process(char ***cmd, int *fds, t_global *global, char **env,
		int backup_fd)
{
	char	*cmd_path;

	if (backup_fd != 0)
	{
		if (dup2(backup_fd, 0) == -1)
			return ;
	}
	if (*(cmd + 1) != NULL)
	{
		if (dup2(fds[1], 1) == -1)
			return (perror("error, dup failed"));
	}
	close(fds[1]);
	close(fds[0]);
	cmd_path = get_command_path((*cmd)[0]);
	if (is_builtin((*cmd)[0]) == 0)
		execute_builtin((*cmd)[0], global);
	else
		execve(cmd_path, *cmd, env);
	free(cmd_path);
	exit(1);
}

// Processus parent
void	parent_process(int *fds, int *backup_fd)
{
	close(fds[1]);
	if (*backup_fd != STDIN_FILENO)
		close(*backup_fd);
	*backup_fd = fds[0];
}

void	execute_pipe(char ***cmd, char **env, t_global *global)
{
	int		fds[2];
	pid_t	pid;
	int		backup_fd;

	backup_fd = STDIN_FILENO;
	while (*cmd)
	{
		if (pipe(fds) == -1)
			exit(1);
		pid = fork();
		if (pid <= -1)
			exit(1);
		if (pid == 0)
			child_process(cmd, fds, global, env, backup_fd);
		else
			parent_process(fds, &backup_fd);
		cmd++;
	}
	while (wait(NULL) > 0)
	{
	}
	signal(SIGINT, SIG_DFL);
}

// void	pipeline(char ***cmd, char **env, t_global *global)
// {
// 	int		fds[2];
// 	pid_t	pid;
// 	int		backup_fd;

// 	backup_fd = STDIN_FILENO;
// 	while (*cmd)
// 	{
// 		if (pipe(fds) == -1)
// 			return (perror("error, pipe failed"));
// 		pid = fork();
// 		if (pid == -1)
// 			return (perror("error, fork failed"));
// 		else if (pid == 0)
// 		{
// 			if (dup2(backup_fd, 0) == -1)
// 				return (perror("error, dup failed"));
// 			child_process(cmd, fds, global, env, backup_fd);
// 		}
// 		else
// 			parent_process(fds, &backup_fd, pid);
// 		cmd++;
// 	}
// }

//// TEST POUR PRINT - A ENLEVER PLUS TARD
// void	print_cmd_array(char *line, char **env, t_global *global,
// 		char ***cmd_array)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (cmd_array[++i])
// 	{
// 		j = -1;
// 		while (cmd_array[i][++j])
// 			printf("[%d - %d] : %s\n", i, j, cmd_array[i][j]);
// 		printf("\n");
// 	}
// }
