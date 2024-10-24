/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:47:59 by jchen             #+#    #+#             */
/*   Updated: 2024/10/23 14:44:33 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

// A FINIR (normalement c bon)
// Tokenise la phrase donnee en argument
void	line_tokenization(t_global **global, int ac, char **av)
{
	char	*token;
	int		beginning;
	int		end;
	int		i;

	i = 0;
	end = -1;
	if (ac == 2)
	{
		while (is_white_space(av[1][i]))
			i++;
		end = end + i;
		stock_line(global, av[1]);
		while ((*global)->line[++end])
		{
			while (is_white_space((*global)->line[end]))
				end++;
			beginning = end;
			while ((*global)->line[end]
				&& !is_white_space((*global)->line[end]))
				end++;
			if (beginning != end)
			{
				token = malloc((end - beginning + 1) * sizeof(char));
				if (!token)
					return ;
				ft_strlcpy(token, &(*global)->line[beginning], end - beginning + 1);
				token[end - beginning] = '\0';
				append_node_to_token_list(global, token);
			}
		}
	}
}

// TEST
// int	main(int ac, char **av)
// {
// 	t_global	*global;
// 	int			i;

// 	if (ac > 1)
// 	{
// 		calloc_global_struct(&global);
// 		i = 1;
// 		while (av[i])
// 		{
// 			line_tokenization(&global, ac, av);
// 			ft_printf("%s\n", global->line);
// 			i++;
// 		}
// 		while (global->token_list)
// 		{
// 			ft_printf("%s\n", global->token_list->token);
// 			global->token_list = global->token_list->next;
// 		}
// 		free_all(global);
// 	}
// }
