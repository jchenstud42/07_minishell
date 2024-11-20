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
/*   Created: 2024/11/12 14:34:39 by jchen             #+#    #+#             */
/*   Updated: 2024/11/12 14:34:39 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
void	add_special_token(t_global *global, char *line, int *end)
{
	char	*token;

	if (is_special_token(&line[*end]) == PIPE
		|| is_special_token(&line[*end]) == INPUT
		|| is_special_token(&line[*end]) == TRUNC)
	{
		token = ft_chardup(line[*end]);
		append_node_to_token_list(&global, token);
		free(token);
		(*end)++;
	}
	else if (is_special_token(&line[*end]) == HEREDOC)
	{
		token = ft_strdup("<<");
		append_node_to_token_list(&global, token);
		free(token);
		*end += 2;
	}
	else if (is_special_token(&line[*end]) == APPEND)
	{
		token = ft_strdup(">>");
		append_node_to_token_list(&global, token);
		free(token);
		*end += 2;
	}
}

char	*line_quote_manager(char *line)
{
	int		i;
	int		j;
	char	*result;
	bool	single_quotes;
	bool	double_quotes;

	i = 0;
	j = 0;
	single_quotes = false;
	double_quotes = false;
	result = malloc(ft_strlen(line) + 1);
	if (!result)
		return (perror("error, line quote malloc failed"), NULL);
	while (line[i])
	{
		if (line[i] == '\'' && !double_quotes)
			single_quotes = !single_quotes;
		else if (line[i] == '"' && !single_quotes)
			double_quotes = !double_quotes;
		else
			result[j++] = line[i];
		i++;
	}
	if (single_quotes || double_quotes)
	{
		free(result);
		return (ft_putstr_fd("bash: error, quotes are not closed\n", 2), NULL);
	}
	result[j] = '\0';
	///// A RETIRER PLUS TARD ///////////////////////////////////////////////
	// printf("quote manager : %s\n", result);
	return (result);
}

// Tokenise la phrase entree apres le prompt
void	line_tokenization(t_global **global, char *line)
{
	char	*token;
	int		beginning;
	int		end;

	free_token_list(&(*global)->token_list);
	line = line_quote_manager(line);
	if (!line)
		return ;
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
		add_special_token(*global, line, &end);
	}
	free(line);
}
