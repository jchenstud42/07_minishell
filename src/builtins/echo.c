/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:07:37 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/21 12:42:20 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(int nbr_caract, char **av)
{
	int	i;
	int	add_line;

	i = 1;
	add_line = 1;
	if (av[i] && check_n(av[i]))
	{
		add_line = 0;
		i++;
	}
	while (i < nbr_caract)
	{
		write(1, av[i], ft_strlen(av[i]));
		if (i != nbr_caract - 1)
			write(1, " ", 1);
		i++;
	}
	if (add_line == 0)
		write(1, "\n", 1);
}

void	ft_echo(char **av)
{
	int	nbr_caract;

	nbr_caract = 0;
	while (av[nbr_caract])
		nbr_caract++;
	print_echo(nbr_caract, av);
}

bool	check_n(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (false);
	if (line[i] && line[i] == '-')
	{
		i++;
		while (line[i] && line[i] == 'n')
			i++;
		if (i == ft_strlen(line))
			return (true);
	}
	return (false);
}
