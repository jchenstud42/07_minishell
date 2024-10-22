/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:00:20 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/22 17:00:12 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		return (TRUE);
	return (FALSE);
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
