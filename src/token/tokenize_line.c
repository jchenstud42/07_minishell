/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/22 15:47:59 by jchen             #+#    #+#             */
/*   Updated: 2024/11/01 12:54:35 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Permet de stocker la ligne de commande dans notre structure
void	stock_line(t_global **global, char *line)
{
	if (!line)
		return (perror("error, empty line"));
	if ((*global)->line)
		free((*global)->line);
	(*global)->line = ft_strdup(line);
	if (!(*global)->line)
		return (perror("error, malloc failed"));
}

// Passe les espaces au debut de la phrase s'il y en a
static void	skip_beginning_white_space(int *end, char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (perror("error, empty line"));
	*end = 0;
	while (is_white_space(line[i]))
		i++;
	*end += i;
}

// Ajoute tous les tokens qui ne sont pas des CMD ou des ARG
void	add_special_token(t_global *global, int *end)
{
	char	*token;

	if (is_special_token(&global->line[*end]) == PIPE
		|| is_special_token(&global->line[*end]) == INPUT
		|| is_special_token(&global->line[*end]) == TRUNC)
	{
		token = ft_chardup(global->line[*end]);
		append_node_to_token_list(&global, token);
		free(token);
		(*end)++;
	}
	else if (is_special_token(&global->line[*end]) == HEREDOC)
	{
		token = ft_strdup("<<");
		append_node_to_token_list(&global, token);
		free(token);
		*end += 2;
	}
	else if (is_special_token(&global->line[*end]) == APPEND)
	{
		token = ft_strdup(">>");
		append_node_to_token_list(&global, token);
		free(token);
		*end += 2;
	}
}

// // Tokenise la phrase entree apres le prompt
void	line_tokenization(t_global **global, char *line)
{
	char	*token;
	int		beginning;
	int		end;

	free_token_list(&(*global)->token_list);
	skip_beginning_white_space(&end, line);
	while (line[end])
	{
		while (is_white_space(line[end]))
			end++;
		beginning = end;
		while (line[end] && !is_white_space(line[end])
			&& !is_special_token(&line[end]))
			end++;
		if (beginning != end)
		{
			token = malloc((end - beginning + 1) * sizeof(char));
			if (!token)
				return (perror("error, line tokenization malloc failed"));
			ft_strlcpy(token, &line[beginning], end - beginning + 1);
			append_node_to_token_list(global, token);
			free(token);
		}
		add_special_token(*global, &end);
	}
}
