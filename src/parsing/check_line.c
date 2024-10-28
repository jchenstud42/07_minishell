/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:00:20 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/28 10:17:37 by rbouquet         ###   ########.fr       */
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

// int	first_token(t_global *global, t_token *token_list)
// {
// 	if (!token_list)
// 		return (0);
// 	else if (token_list->type == PIPE)
// 		return (PIPE);
// 	else if (token_list->type == )
// }

// int	check_line(t_global *global, t_token *token_list)
// {
// 	if (quote_are_closed(global) == 0)
// 		return (0);
// 	else if (first_token(global, token_list) == PIPE)
// 		return (0);
// }

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
