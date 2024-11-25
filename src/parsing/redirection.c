/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:03:59 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/25 15:24:13 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Verifie si le dernier token de notre liste est une redirection
bool	last_token_redirection(t_token *token_list)
{
	t_token	*last_node;

	if (!token_list)
		return (false);
	last_node = last_element_of_list(token_list);
	if (last_node->type == INPUT || last_node->type == HEREDOC
		|| last_node->type == TRUNC || last_node->type == APPEND)
		return (true);
	return (false);
}

// Verifie si une redirection est suivie par une redirection
bool	invalid_redirection(t_token *token_list, t_global *global)
{
	if (!token_list | !global)
		return (false);
	if (token_list->next && ((token_list->type == INPUT
				&& !(ft_strncmp(token_list->next->token, "<", 1)))
			|| (token_list->type == HEREDOC
				&& !(ft_strncmp(token_list->next->token, "<<", 1)))
			|| (token_list->type == TRUNC
				&& !(ft_strncmp(token_list->next->token, ">", 1)))
			|| (token_list->type == APPEND
				&& !(ft_strncmp(token_list->next->token, ">>", 1)))))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(token_list->token, 2);
		ft_putstr_fd("'\n", 2);
		return (global->exit_value = 2, true);
	}
	else if (last_token_redirection(token_list))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			2);
		return (global->exit_value = 2, true);
	}
	return (false);
}

// Verifie si le token est autre chose qu'un ARG
int	is_special_token(char *token)
{
	if (!token || !token[0])
		return (0);
	if (token[0] == '|')
		return (PIPE);
	else if (token[0] == '<')
	{
		if (token[1] == '<')
			return (HEREDOC);
		else
			return (INPUT);
	}
	else if (token[0] == '>')
	{
		if (token[1] == '>')
			return (APPEND);
		else
			return (TRUNC);
	}
	return (0);
}

// Verifie si l'element est une redirection (INPUT, HEREDOC, TRUNC, APPEND)
int	is_redirection(char *str)
{
	if (!ft_strcmp(str, "<") || !ft_strcmp(str, "<<") || !ft_strcmp(str, ">")
		|| !ft_strcmp(str, ">>"))
		return (0);
	return (1);
}

int	redirect_append(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell:", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	redirect_truncate(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell:", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	redirect_input(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell:", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
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
		if (token_list->type == APPEND)
			redirect_append(token_list->next->token); //>>
		else if (token_list->type == TRUNC)
			redirect_truncate(token_list->next->token); //>
		else if (token_list->type == INPUT)
			redirect_input(token_list->next->token); //<
		else if (token_list->type == HEREDOC)
			in_heredoc(global, &token_list->next->token[0]); //<<
		token_list = token_list->next;
	}
}
