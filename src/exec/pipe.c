/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:20:49 by jchen             #+#    #+#             */
/*   Updated: 2024/10/31 15:00:12 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../inc/minishell.h"

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

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	pipe_example(int ac, char **av)
{
	int		temp_infile;
	int		temp_outfile;
	int		fd_infile;
	int		fd_outfile;
	int		pid;
	int		fds[2];
	int		i;
	char	*args[] = {"ls", NULL};

	i = 0;
	temp_infile = dup(0);
	temp_outfile = dup(1);
	// if (infile)
	// 	fd_infile = open(infile, O_RDONLY);
	// else
	fd_infile = dup(temp_infile);
	while (i < ac)
	{
		dup2(fd_infile, 0);
		close(fd_infile);
		if (i + 1 == ac)
			// if (outfile)
			// 	fd_outfile = open(outfile, ???);
			// else
			fd_outfile = dup(temp_outfile);
		else
		{
			pipe(fds);
			fd_outfile = fds[1];
			fd_infile = fds[0];
		}
		dup2(fd_outfile, 1);
		close(fd_outfile);
		pid = fork();
		if (pid == 0)
		{
			execvp(args[0], args);
			exit(1);
		}
		i++;
	}
	dup2(temp_infile, 0);
	dup2(temp_outfile, 1);
	close(temp_infile);
	close(temp_outfile);
	while (1)
	{
		waitpid(pid, NULL, 0);
	}
}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <command1> <command2> ...\n", argv[0]);
		return (1);
	}
	pipe_example(argc - 1, argv + 1);
	return (0);
}
