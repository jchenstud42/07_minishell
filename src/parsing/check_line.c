/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:56:07 by jchen             #+#    #+#             */
/*   Updated: 2024/11/04 18:13:03 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Verifie si les guillemet sont bien fermees
bool	quote_are_closed(char *line)
{
	int	i;
	int	quote_count;

	if (!line)
		return (false);
	i = 0;
	quote_count = 0;
	while (line[i])
	{
		if (line[i] == '"')
			quote_count++;
		i++;
	}
	if (quote_count % 2 == 0)
		return (true);
	return (false);
}

int	first_token_pipe(t_token *token_list)
{
	if (!token_list)
		return (perror("error, empty token list"), 1);
	if (token_list->type == PIPE)
		return (PIPE);
	return (0);
}

int	last_token_redirection(t_token *token_list)
{
	t_token	*last_node;

	if (!token_list)
		return (perror("error, empty token list"), 1);
	last_node = last_element_of_list(token_list);
	if (last_node->type == INPUT || last_node->type == HEREDOC
		|| last_node->type == TRUNC || last_node->type == APPEND)
		return (0);
	return (1);
}

int	check_line(t_global *global, t_token *token_list)
{
	if (quote_are_closed(global->line) == false)
		return (perror("error, quotes are open"), 1);
	if (first_token_pipe(token_list) == PIPE)
		return (ft_putstr_fd("bash: syntax error near unexpected token `|'\n",
				2), 1);
	else if (last_token_redirection(token_list) == 0)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
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
