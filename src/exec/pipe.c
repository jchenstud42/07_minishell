/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:20:49 by jchen             #+#    #+#             */
/*   Updated: 2024/11/01 17:59:37 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// int	pipe_example(void)
// {
// 	int			fds[2];
// 	pid_t		pid;
// 	const char	*words[] = {"pear", "peach", "apple"};
// 	size_t		numwords;
// 	int			status;
// 	pid_t		wpid;

// 	pipe(fds);
// 	pid = fork();
// 	if (pid < 0)
// 		return ;
// 	if (pid == 0)
// 	{
// 		dup2(fds[0], STDIN_FILENO);
// 		close(fds[0]);
// 		close(fds[1]);
// 		char *argv[] = {(char *)"sort", NULL}; // create argument vector
// 		if (execvp(argv[0], argv) < 0)
// 			exit(0); // run sort command (exit if something went wrong)
// 	}
// 	// if we reach here, we are in parent process
// 	close(fds[0]); // file descriptor unused in parent
// 	// write input to the writable file descriptor so it can be read in from child:
// 	numwords = sizeof(words) / sizeof(words[0]);
// 	for (size_t i = 0; i < numwords; i++)
// 	{
// 		dprintf(fds[1], "%s\n", words[i]);
// 	}
// 	// send EOF so child can continue (child blocks until all input has been processed):
// 	close(fds[1]);
// 	wpid = waitpid(pid, &status, 0);
// 	// wait for child to finish before exiting
// 	return (wpid == pid && WIFEXITED(status) ? WEXITSTATUS(status) : -1);
// }

// int	pipe_example(t_global *global)
// {
// 	int			temp_infile;
// 	int			temp_outfile;
// 	int			fd_infile;
// 	int			fd_outfile;
// 	t_global	*temp;
// 	int			nbr_command;
// 	int			pid;
// 	int			fd_outfile;
// 	int			fds[2];

// 	temp = global;
// 	nbr_command = 0;
// 	while (temp)
// 	{
// 		if (temp->token_list->type == CMD)
// 			nbr_command++;
// 		temp->token_list = temp->token_list->next;
// 	}
// 	temp_infile = dup(0);
// 	temp_outfile = dup(1);
// 	// if (infile)
// 	// 	fd_infile = open(infile, O_RDONLY);
// 	// else
// 	fd_infile = dup(temp_infile);
// 	while (nbr_command > 0)
// 	{
// 		dup2(fd_infile, 0);
// 		close(fd_infile);
// 		if (nbr_command - 1 == 0)
// 			// if (outfile)
// 			// 	fd_outfile = open(outfile, ???);
// 			// else
// 			fd_outfile = dup(temp_outfile);
// 		else
// 		{
// 			pipe(fds);
// 			fd_outfile = pipe[1];
// 			fd_infile = pipe[0];
// 		}
// 		dup2(fd_outfile, 1);
// 		close(fd_outfile);
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			execvp();
// 			exit(1);
// 		}
// 		nbr_command--;
// 	}
// 	dup2(temp_infile, 0);
// 	dup2(temp_outfile, 1);
// 	close(temp_infile);
// 	close(temp_outfile);
// 	if (!background)
// 		waitpid(pid, NULL);
// }

// Remplie un tableau de string d'arguments qui vont etre utilises par execve()
// On en profite pour passer les noeuds possedant des ARG
// char	***fill_pipe_command_array(t_global *global)
// {
// 	char	**execve_args;
// 	int		nbr_arg;
// 	int		i;

// 	i = -1;
// 	nbr_arg = nbr_arg_after_cmd(global);
// 	execve_args = malloc((nbr_arg + 1) * sizeof(char *));
// 	if (!execve_args)
// 	{
// 		free(execve_args);
// 		error_handler(MALLOC_FAILED, global);
// 	}
// 	while (nbr_arg > ++i)
// 	{
// 		execve_args[i] = ft_strdup(global->token_list->token);
// 		if (!execve_args[i])
// 		{
// 			free_array(execve_args);
// 			error_handler(MALLOC_FAILED, global);
// 		}
// 		global->token_list = global->token_list->next;
// 	}
// 	execve_args[i] = NULL;
// 	return (execve_args);
// }

char	***fill_cmd_double_array(t_token *token_list, char ***cmd_arrays,
		t_global *global)
{
	t_token	*current_token;
	int		i;

	if (!token_list || !cmd_arrays)
		return (NULL);
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

void	execute_pipe(char *line, char **env, t_global *global)
{
	char	***cmd_arrays;
	int		i;
	int		j;

	j = -1;
	if (!line || !env || !global)
		error_handler(STRUCT_INIT_FAILED, global);
	cmd_arrays = init_cmd_double_array(global);
	fill_cmd_double_array(global->token_list, cmd_arrays, global);
	//// TEST POUR PRINT - A ENLEVER PLUS TARD
	i = -1;
	while (cmd_arrays[++i])
	{
		j = -1;
		while (cmd_arrays[i][++j])
			printf("[%d - %d] : %s\n", i, j, cmd_arrays[i][j]);
		printf("\n");
	}
	free_double_array(cmd_arrays);
	return ;
}
// fill_pipe_execve_arg_array(global);
// command_file = get_command_path(cmd, global);
// pid = fork();
// if (pid == -1)
// {
// 	free(command_file);
// 	error_handler(FORK_FAILED, global);
// }
// else if (pid == 0)
// {
// 	execve_args = fill_execve_arg_array(global);
// 	if (execve(command_file, execve_args, env) == -1)
// 		ft_printf("%s: command not found\n", cmd);
// 	free_array(execve_args);
// 	free(command_file);
// 	exit(EXIT_FAILURE);
// }
// else
// 	waitpid(pid, NULL, 0);
// free(command_file);
// }

// static void	pipeline(char ***cmd)
// {
// 	int		fd[2];
// 	pid_t	pid;

// 	int fdd = 0; /* Backup */
// 	while (*cmd != NULL)
// 	{
// 		pipe(fd);
// 		if ((pid = fork()) == -1)
// 		{
// 			perror("fork");
// 			exit(1);
// 		}
// 		else if (pid == 0)
// 		{
// 			dup2(fdd, 0);
// 			if (*(cmd + 1) != NULL)
// 			{
// 				dup2(fd[1], 1);
// 			}
// 			close(fd[0]);
// 			execvp((*cmd)[0], *cmd);
// 			exit(1);
// 		}
// 		else
// 		{
// 			wait(NULL); /* Collect childs */
// 			close(fd[1]);
// 			fdd = fd[0];
// 			cmd++;
// 		}
// 	}
// }

// int	main(int argc, char *argv[])
// {
// 	char	*ls[] = {"ls", "-al", NULL};
// 	char	*rev[] = {"rev", NULL};
// 	char	*nl[] = {"nl", NULL};
// 	char	*cat[] = {"cat", "-e", NULL};
// 	char	**cmd[] = {ls, rev, nl, cat, NULL};

// 	(void)argc;
// 	(void)argv;
// 	pipeline(cmd);
// 	return (0);
// }
