/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:27:09 by rbouquet          #+#    #+#             */
/*   Updated: 2024/12/11 19:31:37 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	redirect_trunc_append(char *filename, int mode, t_global *global)
{
	int	fd;

	fd = open(filename, mode, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell:", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
		return (1);
	}
	if (global->cmd_list->cmd)
	{
		global->cmd_list->outfile_cmd = fd;
		printf("cmd outfile fd = %d\n", global->cmd_list->outfile_cmd);
		return (0);
	}
	close(fd);
	return (0);
}

static int	redirect_input(char *filename, int mode, t_global *global)
{
	int	fd;

	fd = open(filename, mode, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell:", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
		return (1);
	}
	if (global->cmd_list->cmd)
	{
		global->cmd_list->infile_cmd = fd;
		printf("cmd infile fd = %d\n", global->cmd_list->infile_cmd);
		return (0);
	}
	close(fd);
	return (0);
}

void	handle_redirection(t_global *global, t_token *token_list)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
		return (perror("dup sauvegarde"));
	while (token_list)
	{
		if (token_list->type == TRUNC) // >
		{
			printf("ok 1\n");
			redirect_trunc_append(token_list->next->token,
									O_WRONLY | O_APPEND | O_CREAT,
									global);
		}
		else if (token_list->type == APPEND) // >>
		{
			printf("ok 2\n");
			redirect_trunc_append(token_list->next->token,
									O_WRONLY | O_TRUNC | O_CREAT,
									global);
		}
		else if (token_list->type == INPUT) // <
		{
			printf("ok 3\n");
			redirect_input(token_list->next->token, O_RDONLY, global);
		}
		else if (token_list->type == HEREDOC) // <<
			ft_heredoc(global, token_list->next->token);
		token_list = token_list->next;
	}
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		perror("Restauration stdin");
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		perror("Restauration stdout");
	close(saved_stdin);
	close(saved_stdout);
}

int	redirect(char *filename, int mode, int std_fd)
{
	int	fd;

	fd = open(filename, mode, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell:", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
		return (1);
	}
	if (dup2(fd, std_fd) == -1)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

// void	handle_redirection(t_global *global, t_token *token_list)
// {
// 	int	saved_stdin;
// 	int	saved_stdout;

// 	saved_stdin = dup(STDIN_FILENO);
// 	saved_stdout = dup(STDOUT_FILENO);
// 	if (saved_stdin == -1 || saved_stdout == -1)
// 		return (perror("dup sauvegarde"));
// 	while (token_list)
// 	{
// 		if (token_list->type == TRUNC) // >
// 			redirect(token_list->next->token, O_WRONLY | O_TRUNC | O_CREAT,
// 					STDOUT_FILENO);
// 		else if (token_list->type == APPEND) // >>
// 			redirect(token_list->next->token, O_WRONLY | O_APPEND | O_CREAT,
// 					STDOUT_FILENO);
// 		else if (token_list->type == INPUT) // <
// 			redirect(token_list->next->token, O_RDONLY, STDIN_FILENO);
// 		else if (token_list->type == HEREDOC) // <<
// 			ft_heredoc(global, token_list->next->token);
// 		token_list = token_list->next;
// 	}
// 	if (dup2(saved_stdin, STDIN_FILENO) == -1)
// 		perror("Restauration stdin");
// 	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
// 		perror("Restauration stdout");
// 	close(saved_stdin);
// 	close(saved_stdout);
// }
