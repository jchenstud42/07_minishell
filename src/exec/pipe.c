/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:20:49 by jchen             #+#    #+#             */
/*   Updated: 2024/11/04 17:02:36 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Processus enfant
void	child_process(char ***cmd, int *fds, t_global *global, char **env)
{
	char	*cmd_path;

	if (*(cmd + 1) != NULL)
	{
		if (dup2(fds[1], 1) == -1)
			return (perror("error, dup failed"));
	}
	close(fds[1]);
	close(fds[0]);
	cmd_path = get_command_path((*cmd)[0], global);
	execve(cmd_path, *cmd, env);
	// ---------------------------------------------- PAS NECESSAIRE????????
	// if (execve(cmd_path, *cmd, env) == -1)
	// {
	// 	ft_putstr_fd(*cmd[0], 2);
	// 	ft_putstr_fd(": command not found\n", 2);
	// }
	free(cmd_path);
	exit(1);
}

// Processus parent
void	parent_process(int *fds, int *backup_fd, pid_t pid)
{
	close(fds[1]);
	if (*backup_fd != 0)
		close(*backup_fd);
	*backup_fd = fds[0];
	waitpid(pid, NULL, 0);
}

void	pipeline(char ***cmd, char **env, t_global *global)
{
	int		fds[2];
	pid_t	pid;
	int		backup_fd;

	backup_fd = 0;
	while (*cmd != NULL)
	{
		if (pipe(fds) == -1)
			return (perror("error, pipe failed"));
		pid = fork();
		if (pid == -1)
			return (perror("error, fork failed"));
		else if (pid == 0)
		{
			if (dup2(backup_fd, 0) == -1)
				return (perror("error, dup failed"));
			child_process(cmd, fds, global, env);
			exit(1);
		}
		else
			parent_process(fds, &backup_fd, pid);
		cmd++;
	}
}

// Simule les pipes
// void	pipeline(char ***cmd, char **env, t_global *global)
// {
// 	int		fds[2];
// 	int		backup_fd;
// 	pid_t	pid;

// 	backup_fd = 0;
// 	while (*cmd != NULL)
// 	{
// 		if (pipe(fds) == -1)
// 			return (perror("error, pipe failed"));
// 		// error_handler(PIPE_FAILED, global);
// 		pid = fork();
// 		if (pid == -1)
// 			return (perror("error, fork failed"));
// 		else if (pid == 0)
// 		{
// 			if (dup2(backup_fd, 0) == -1)
// 				return (perror("error, dup failed"));
// 			child_process(cmd, fds, global, env);
// 		}
// 		else
// 		{
// 			close(fds[1]);
// 			if (backup_fd != 0)
// 				close(backup_fd);
// 			backup_fd = fds[0];
// 			waitpid(pid, NULL, 0);
// 		}
// 		cmd++;
// 	}
// }

// Remplie un double tableau de string d'arguments
// qui seront utilises par execve()
char	***fill_cmd_double_array(t_token *token_list, char ***cmd_arrays,
		t_global *global)
{
	t_token	*current_token;
	int		i;

	if (!token_list || !cmd_arrays)
		return (perror("error, empty array"), NULL);
	i = -1;
	current_token = token_list;
	while (current_token)
	{
		if (current_token->type == CMD)
			cmd_arrays[++i] = fill_execve_arg_array(global, current_token);
		current_token = current_token->next;
	}
	return (cmd_arrays);
}

// Prepare et launch le code comme si on utilisait les pipes
void	execute_pipe(char *line, char **env, t_global *global)
{
	char	***cmd_arrays;

	if (!line || !env || !global)
		return (perror("error, pipe execution"));
	cmd_arrays = init_cmd_double_array(global);
	fill_cmd_double_array(global->token_list, cmd_arrays, global);
	//// TEST POUR PRINT - A ENLEVER PLUS TARD //////////////////////////////
	// i = -1;
	// while (cmd_arrays[++i])
	// {
	// 	j = -1;
	// 	while (cmd_arrays[i][++j])
	// 		printf("[%d - %d] : %s\n", i, j, cmd_arrays[i][j]);
	// 	printf("\n");
	// }
	//// FIN TEST POUR PRINT /////////////////////////////////////////////////
	pipeline(cmd_arrays, env, global);
	free_double_array(cmd_arrays);
}
