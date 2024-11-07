/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:07:37 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/07 19:12:45 by jchen            ###   ########.fr       */
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

// il faudra modifier le write, pour qu'il redirige vers un fd
// precis, car on peut write dans un fichier par exemple
void	print_echo(int nbr_caract, char **cmd_list)
{
	int	i;
	int	add_line;

	i = 0;
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

// IL FAUT QUE TOUS LES BUILTINS SOIENT EN INT POUR L'EXIT VALUE
void	ft_echo(char **cmd_list)
{
	int	nbr_caract;

	nbr_caract = 0;
	while (cmd_list[nbr_caract])
		nbr_caract++;
	print_echo(nbr_caract, cmd_list);
}
