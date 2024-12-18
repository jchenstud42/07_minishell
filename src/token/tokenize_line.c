/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:23:24 by rbouquet          #+#    #+#             */
/*   Updated: 2024/12/18 09:23:27 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Ajoute tous les tokens qui ne sont pas des CMD ou des ARG
static void	add_special_token(t_global *global, char *line, int *end)
{
	char	*token;

	if (str_is_special_token(&line[*end]) == PIPE
		|| str_is_special_token(&line[*end]) == INPUT
		|| str_is_special_token(&line[*end]) == OUTPUT)
	{
		token = ft_chardup(line[*end]);
		append_node_to_token_list(&global, token);
		free(token);
		(*end)++;
	}
	else if (str_is_special_token(&line[*end]) == HEREDOC)
	{
		token = ft_strdup("<<");
		append_node_to_token_list(&global, token);
		free(token);
		*end += 2;
	}
	else if (str_is_special_token(&line[*end]) == APPEND)
	{
		token = ft_strdup(">>");
		append_node_to_token_list(&global, token);
		free(token);
		*end += 2;
	}
}

// static void	browse_line(char **line, int *end, int *beginning)
// {
// 	char	quote_type;

// 	while (is_white_space((*line)[*end]))
// 		(*end)++;
// 	*beginning = *end;
// 	if ((*line)[*end] == '\'' || (*line)[*end] == '"')
// 	{
// 		quote_type = (*line)[*end];
// 		*beginning = (*end)++;
// 		while ((*line)[*end] && (*line)[*end] != quote_type)
// 			(*end)++;
// 		while ((*line)[*end] && !is_white_space((*line)[*end]))
// 			(*end)++;
// 		if ((*line)[*end] == quote_type)
// 			(*end)++;
// 	}
// 	else
// 	{
// 		while ((*line)[*end] && !is_white_space((*line)[*end])
// 			&& !str_is_special_token(&(*line)[*end]) && (*line)[*end] != '\''
// 			&& (*line)[*end] != '"')
// 			(*end)++;
// 		if ((*line)[*end] == '\'' || (*line)[*end] == '"')
// 		{
// 			quote_type = (*line)[*end];
// 			(*end)++;
// 			while ((*line)[*end] && (*line)[*end] != quote_type)
// 				(*end)++;
// 			while ((*line)[*end] && !is_white_space((*line)[*end]))
// 				(*end)++;
// 			if ((*line)[*end] == quote_type)
// 				(*end)++;
// 		}
// 		while ((*line)[*end] && !is_white_space((*line)[*end])
// 			&& !str_is_special_token(&(*line)[*end]) && (*line)[*end] != '\''
// 			&& (*line)[*end] != '"')
// 			(*end)++;
// 	}
// }

static void	process_quotes(char **line, int *end)
{
	char	quote_type;

	quote_type = (*line)[*end];
	(*end)++;
	while ((*line)[*end] && (*line)[*end] != quote_type)
		(*end)++;
	if ((*line)[*end] == quote_type)
		(*end)++;
	while ((*line)[*end] && !is_white_space((*line)[*end]))
		(*end)++;
}

static void	browse_line(char **line, int *end, int *beginning)
{
	while (is_white_space((*line)[*end]))
		(*end)++;
	*beginning = *end;
	if ((*line)[*end] == '\'' || (*line)[*end] == '"')
		process_quotes(line, end);
	else
	{
		while ((*line)[*end] && !is_white_space((*line)[*end])
			&& !str_is_special_token(&(*line)[*end]) && (*line)[*end] != '\''
			&& (*line)[*end] != '"')
			(*end)++;
		if ((*line)[*end] == '\'' || (*line)[*end] == '"')
			process_quotes(line, end);
		while ((*line)[*end] && !is_white_space((*line)[*end])
			&& !str_is_special_token(&(*line)[*end]) && (*line)[*end] != '\''
			&& (*line)[*end] != '"')
			(*end)++;
	}
}

void	line_tokenization(t_global **global, char **line)
{
	char	*token;
	int		beginning;
	int		end;

	free_token_list(&(*global)->token_list);
	if ((ft_strchr((*line), '$')))
		*line = dollar_parsing(*global, *line);
	if (!*line || !quotes_are_closed(*line))
		return ;
	skip_beginning_white_space(&end, *line);
	while ((*line)[end])
	{
		browse_line(line, &end, &beginning);
		if (beginning != end)
		{
			token = malloc((end - beginning + 1) * sizeof(char));
			if (!token)
				return (perror("error, line tokenization malloc failed"));
			ft_strlcpy(token, &(*line)[beginning], end - beginning + 1);
			append_node_to_token_list(global, token);
			free(token);
		}
		add_special_token(*global, *line, &end);
	}
}

// static void	browse_line(char **line, int *end, int *beginning)
// {
// 	char	quote_type;

// 	while (is_white_space((*line)[*end]))
// 		(*end)++;
// 	*beginning = *end;
// 	if ((*line)[*end] == '\'' || (*line)[*end] == '"')
// 	{
// 		quote_type = (*line)[*end];
// 		*beginning = (*end)++;
// 		while ((*line)[*end] && (*line)[*end] != quote_type)
// 			(*end)++;
// 		while ((*line)[*end] && !is_white_space((*line)[*end]))
// 			(*end)++;
// 		if ((*line)[*end] == quote_type)
// 			(*end)++;
// 	}
// 	else
// 	{
// 		while ((*line)[*end] && !is_white_space((*line)[*end])
// 			&& !str_is_special_token(&(*line)[*end]))
// 			(*end)++;
// 	}
// }

// void	line_tokenization(t_global **global, char **line)
// {
// 	char	*token;
// 	int		beginning;
// 	int		end;

// 	free_token_list(&(*global)->token_list);
// 	if ((ft_strchr((*line), '$')))
// 		*line = dollar_parsing(*global, *line);
// 	if (!*line || !quotes_are_closed(*line))
// 		return ;
// 	skip_beginning_white_space(&end, *line);
// 	while ((*line)[end])
// 	{
// 		browse_line(line, &end, &beginning);
// 		if (beginning != end)
// 		{
// 			token = malloc((end - beginning + 1) * sizeof(char));
// 			if (!token)
// 				return (perror("error, line tokenization malloc failed"));
// 			ft_strlcpy(token, &(*line)[beginning], end - beginning + 1);
// 			append_node_to_token_list(global, token);
// 			free(token);
// 		}
// 		add_special_token(*global, *line, &end);
// 	}
// }
