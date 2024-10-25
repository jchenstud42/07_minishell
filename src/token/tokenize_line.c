/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:47:59 by jchen             #+#    #+#             */
/*   Updated: 2024/10/25 14:02:01 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Permet de stocker la ligne de commande dans notre structure
void	stock_line(t_global **global, char *line)
{
	if (!line)
		error_handler(EMPTY_LINE, *global);
	if ((*global)->line)
		free((*global)->line);
	(*global)->line = ft_strdup(line);
	if (!(*global)->line)
		error_handler(MALLOC_FAILED, *global);
}

// Tokenise la phrase entree apres le prompt
void	line_tokenization(t_global **global, char *line)
{
	char	*token;
	int		beginning;
	int		end;
	int		i;

	free_token_list(&(*global)->token_list);
	i = 0;
	end = -1;
	while (is_white_space(line[i]))
		i++;
	end = end + i;
	stock_line(global, line);
	while ((*global)->line[++end])
	{
		while (is_white_space((*global)->line[end]))
			end++;
		beginning = end;
		while ((*global)->line[end] && !is_white_space((*global)->line[end]))
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
