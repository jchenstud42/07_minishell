/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:12:55 by rbouquet          #+#    #+#             */
/*   Updated: 2024/12/18 09:26:11 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_n(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	if (line[i] && line[i] == '-' && line[i + 1] == 'n')
	{
		i++;
		while (line[i] && line[i] == 'n')
			i++;
		if (i == (int)ft_strlen(line))
			return (1);
	}
	return (0);
}

void	print_echo(int nbr_caract, int i, char **cmd_list)
{
	int	add_line;

	add_line = 1;
	while (i < nbr_caract && check_n(cmd_list[i]))
	{
		add_line = 0;
		++i;
	}
	while (i < nbr_caract)
	{
		write(1, cmd_list[i], ft_strlen(cmd_list[i]));
		if (i != nbr_caract - 1)
			write(1, " ", 1);
		i++;
	}
	if (add_line == 1)
		write(1, "\n", 1);
}

int	ft_echo(t_global *global, char **cmd_list)
{
	int	nbr_caract;
	int	i;

	i = 1;
	nbr_caract = 0;
	while (cmd_list[nbr_caract])
		nbr_caract++;
	print_echo(nbr_caract, i, cmd_list);
	global->exit_value = 0;
	return (0);
}
