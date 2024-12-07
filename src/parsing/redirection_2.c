/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:27:09 by rbouquet          #+#    #+#             */
/*   Updated: 2024/12/07 11:58:56 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// int	redirect_append(char *filename)
// {
// 	int	fd;

// 	fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
// 	if (fd == -1)
// 	{
// 		ft_putstr_fd("minishell:", 2);
// 		ft_putstr_fd(filename, 2);
// 		ft_putstr_fd(" : No such file or directory\n", 2);
// 		return (1);
// 	}
// 	if (dup2(fd, STDOUT_FILENO) == -1)
// 	{
// 		perror("dup2");
// 		close(fd);
// 		return (1);
// 	}
// 	close(fd);
// 	return (0);
// }

// int	redirect_truncate(char *filename)
// {
// 	int	fd;

// 	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
// 	if (fd == -1)
// 	{
// 		ft_putstr_fd("minishell:", 2);
// 		ft_putstr_fd(filename, 2);
// 		ft_putstr_fd(" : No such file or directory\n", 2);
// 		return (1);
// 	}
// 	if (dup2(fd, STDOUT_FILENO) == -1)
// 	{
// 		perror("dup2");
// 		close(fd);
// 		return (1);
// 	}
// 	close(fd);
// 	return (0);
// }

// int	redirect_input(char *filename)
// {
// 	int	fd;

// 	fd = open(filename, O_RDONLY, 0644);
// 	if (fd == -1)
// 	{
// 		ft_putstr_fd("minishell:", 2);
// 		ft_putstr_fd(filename, 2);
// 		ft_putstr_fd(" : No such file or directory\n", 2);
// 		return (1);
// 	}
// 	if (dup2(fd, STDIN_FILENO) == -1)
// 	{
// 		perror("dup2");
// 		close(fd);
// 		return (1);
// 	}
// 	close(fd);
// 	return (0);
// }

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

void	handle_redirection(t_global *global, t_token *token_list)
{
	while (token_list)
	{
		if (token_list->type == APPEND) // >
		{
			printf("ok");
			redirect(token_list->next->token, O_WRONLY | O_APPEND | O_CREAT,
				STDOUT_FILENO);
		}
		else if (token_list->type == TRUNC) // >>
			redirect(token_list->next->token, O_WRONLY | O_TRUNC | O_CREAT,
				STDOUT_FILENO);
		else if (token_list->type == INPUT) // <
			redirect(token_list->next->token, O_RDONLY, STDIN_FILENO);
		else if (token_list->type == HEREDOC) // <<
			in_heredoc(global, token_list->next->token);
		token_list = token_list->next;
	}
}
