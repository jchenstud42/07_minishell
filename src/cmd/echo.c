/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:07:37 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/15 10:25:45 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(int count_arg, char **av)
{
	int	i;

	i = 1;
	while (i < count_arg)
	{
		write(1, av[i], ft_strlen(av[i]));
		i++;
	}
	if (check_n == 1)
		ft_printf('\n');
}

void	ft_echo(char **av)
{
	int	count_arg;

	count_arg = 0;
	while (av[count_arg])
		count_arg++;
	print_echo(count_arg, av);
}

int	check_n(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '-' && line[i + 1] == 'n')
			return (1);
		i++;
	}
	return (0);
}