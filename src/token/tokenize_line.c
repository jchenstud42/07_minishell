/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:47:59 by jchen             #+#    #+#             */
/*   Updated: 2024/10/22 19:49:06 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Permet de stocker tous les arguments dans la structure
// Pas utile en realite ??
// void	stock_line(t_global **global, char *line)
// {
// 	char	*new_line;

// 	if (!line)
// 		error_handler(EMPTY_LINE, *global);
// 	if (!(*global)->line)
// 	{
// 		(*global)->line = malloc((ft_strlen(line) + 1));
// 		if (!(*global)->line)
// 			error_handler(MALLOC_FAILED, *global);
// 		ft_strlcpy((*global)->line, line, ft_strlen(new_line) + 1);
// 	}
// 	else
// 	{
// 		new_line = malloc((ft_strlen(line) + ft_strlen((*global)->line) + 1));
// 		if (!new_line)
// 			error_handler(MALLOC_FAILED, *global);
// 		ft_strlcpy(new_line, (*global)->line, ft_strlen((*global)->line) + 1);
// 		ft_strlcat(new_line, line, (ft_strlen(line) + ft_strlen((*global)->line)
// 				+ 1));
// 		free((*global)->line);
// 		(*global)->line = new_line;
// 	}
// }

// Permet de stocker l'argument dans notre structure
void	stock_line(t_global **global, char *line)
{
	if (!line)
		error_handler(EMPTY_LINE, *global);
	if ((*global)->line)
		free((*global)->line);
	(*global)->line = malloc((ft_strlen(line) + 1));
	if (!(*global)->line)
		error_handler(MALLOC_FAILED, *global);
	ft_strlcpy((*global)->line, line, ft_strlen(line) + 1);
}

// A FINIR
// Tokenise la phrase donnee en argument
void	line_tokenization(t_global **global, int ac, char **av)
{
	char	*line;
	int		beginning;
	int		end;

	end = -1;
	if (ac == 2)
	{
		stock_line(global, av[1]);
		while ((*global)->line[++end])
		{
			beginning = end;
			while ()
		}
	}
}

// TEST
int	main(int ac, char **av)
{
	t_global	*global;
	int			i;

	if (ac > 1)
	{
		calloc_global_struct(&global);
		i = 1;
		while (av[i])
		{
			stock_line(&global, av[i]);
			ft_printf("%s\n", global->line);
			i++;
		}
		free_all(global);
	}
}
