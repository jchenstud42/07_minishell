/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/15 11:00:20 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/31 11:28:05 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


// Compte le nombre de pipe
int	count_pipe(char *line)
{
	int i;
	int pipe_count;

	if (!line)
		return (ERROR);
	i = 0;
	pipe_count = 0;
	while (line[i])
	{
		if (line[i] == '|')
			pipe_count++;
		i++;
	}
	return (pipe_count);
}

// Verifie si les guillemet sont bien fermees
int	quote_are_closed(char *line)
{
	int i;
	int quote_count;

	if (!line)
		return (ERROR);
	i = 0;
	quote_count = 0;
	while (line[i])
	{
		if (line[i] == '"')
			quote_count++;
		i++;
	}
	if (quote_count % 2 == 0)
		return (1);
	return (0);
}

int	first_token_pipe(t_token *token_list)
{
	if (!token_list)
		return (0);
	if (token_list->type == PIPE)
		return (PIPE);
	return (0);
}

int	last_token_redirection(t_token *token_list)
{
	t_token *last_node;

	if (!token_list)
		return (-1);
	last_node = last_element_of_list(token_list);
	if (last_node->type == INPUT || last_node->type == HEREDOC
		|| last_node->type == TRUNC || last_node->type == APPEND)
		return (0);
	return (1);
}

int	check_line(t_global *global, t_token *token_list)
{
	if (quote_are_closed(global->line) == 0)
		return (0);
	if (first_token_pipe(token_list) == PIPE)
	{
		write(2, "bash: syntax error near unexpected token `|'\n", 45);
		return (1);
	}
	else if (last_token_redirection(token_list) == 0)
	{
		write(2, "bash: syntax error near unexpected token `newline'\n", 51);
		return (1);
	}
	else
		return (0);
}

// TEST
// int	main(int ac, char **av)
// {
// 	if (ac > 1)
// 	{
// 		ft_printf("pipe number : %d\n", count_pipe(av[1]));
// 		if (quote_are_closed(av[1]))
// 			ft_printf("quotes are closed\n");
// 		else if (!quote_are_closed(av[1]))
// 			ft_printf("quotes aren't closed\n");
// 	}
// 	return (0);
// }
