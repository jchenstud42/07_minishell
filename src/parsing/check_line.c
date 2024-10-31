/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:00:20 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/31 10:36:21 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Compte le nombre de pipe
int	count_pipe(char *line)
{
	int	i;
	int	pipe_count;

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
	int	i;
	int	quote_count;

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
	else if (token_list->type == PIPE)
		return (PIPE);
	return (0);
}

int	last_token(t_token *token_list)
{
	t_token	*tmp;

	if (!token_list)
	{
		ft_printf("AAAAA"); // ca rentre dedans je ne sais pas pourquoi
		return (0);
	}
	tmp = token_list;
	while (tmp->next != token_list)
		tmp = tmp->next;
	if (tmp->type == INPUT || tmp->type == HEREDOC
		|| tmp->type == TRUNC || tmp->type == APPEND)
		return (0);
	return (1);
}

int	check_line(t_global *global, t_token *token_list)
{
	if (quote_are_closed(global->line) == 0)
		return (0);
	else if (first_token_pipe(token_list) == PIPE)
	{
		ft_printf("bash: syntax error near unexpected token `|'\n");
		return (0);
	}
	else if (last_token(token_list) == 0)
	{
		ft_printf("bash: syntax error near unexpected token `newline'\n");
		return (0);
	}
	else
		return (1);
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
