/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:27:09 by rbouquet          #+#    #+#             */
/*   Updated: 2024/12/14 19:17:39 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	redirect_trunc_append(char *filename, t_global *global, int mode)
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
	global->cmd_list->outfile_cmd = fd;
	return (0);
}

static int	redirect_input(char *filename, t_global *global, int mode)
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
	global->cmd_list->infile_cmd = fd;
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
		if (cmd->infile_cmd == INPUT) // <
			redirect_input(cmd->filename, global, O_RDONLY);
		else if (cmd->infile_cmd == HEREDOC) // <<
			ft_heredoc(global, cmd->filename, cmd);
		else if (cmd->outfile_cmd == OUTPUT) // >
			redirect_trunc_append(cmd->filename, global,
					O_WRONLY | O_TRUNC | O_CREAT);
		else if (cmd->outfile_cmd == APPEND) // >>
			redirect_trunc_append(cmd->filename, global,
					O_WRONLY | O_APPEND | O_CREAT);
		cmd = cmd->next;
	}
	if (dup2(saved_stdin, STDIN_FILENO) == -1 || dup2(saved_stdout,
			STDOUT_FILENO) == -1)
		perror("Restauration stdout/stdin");
	return (close(saved_stdin), close(saved_stdout));
}

// int	handle_redirection(t_global *global, t_token *token_list)
// {
// 	int	saved_stdin;
// 	int	saved_stdout;

// 	printf("enter in handle redirection\n");
// 	saved_stdin = dup(STDIN_FILENO);
// 	saved_stdout = dup(STDOUT_FILENO);
// 	if (saved_stdin == -1 || saved_stdout == -1)
// 		return (perror("dup sauvegarde"), 1);
// 	while (token_list)
// 	{
// 		if (token_list->type == OUTPUT) // >
// 		{
// 			printf("(>)\n");
// 			redirect_trunc_append(token_list->next->token, global,
// 					O_WRONLY | O_TRUNC | O_CREAT);
// 		}
// 		else if (token_list->type == APPEND) // >>
// 		{
// 			printf("(>>)\n");
// 			redirect_trunc_append(token_list->next->token, global,
// 					O_WRONLY | O_APPEND | O_CREAT);
// 		}
// 		else if (token_list->type == INPUT) // <
// 		{
// 			printf("(<)\n");
// 			redirect_input(token_list->next->token, global, O_RDONLY);
// 		}
// 		else if (token_list->type == HEREDOC) // <<
// 		{
// 			printf("(<<)\n");
// 			ft_heredoc(global, token_list->next->token);
// 		}
// 		token_list = token_list->next;
// 	}
// 	if (dup2(saved_stdin, STDIN_FILENO) == -1 || dup2(saved_stdout,
// 			STDOUT_FILENO) == -1)
// 		perror("Restauration stdout/stdin");
// 	return (close(saved_stdin), close(saved_stdout));
// }
