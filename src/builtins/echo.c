/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/11/08 15:57:45 by jchen             #+#    #+#             */
/*   Updated: 2024/11/08 15:57:45 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


int	check_n(char *line)
{
	int i;

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

// il faudra modifier le write, pour qu'il redirige vers un fd
// precis, car on peut write dans un fichier par exemple
void	print_echo(int nbr_caract, int i, char **cmd_list, int fd)
{
	int add_line;

	add_line = 1;
	while (i < nbr_caract && check_n(cmd_list[i]))
	{
		add_line = 0;
		++i;
	}
	while (i < nbr_caract)
	{
		write(fd, cmd_list[i], ft_strlen(cmd_list[i]));
		if (i != nbr_caract - 1)
			write(1, " ", 1);
		i++;
	}
	if (add_line == 1)
		write(fd, "\n", 1);
}

int	ft_echo(char **cmd_list, int fd)
{
	int nbr_caract;
	int i;

	i = 1;
	nbr_caract = 0;
	while (cmd_list[nbr_caract])
		nbr_caract++;
	print_echo(nbr_caract, i, cmd_list, fd);
	return (0);
}
