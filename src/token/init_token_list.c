/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:47:41 by jchen             #+#    #+#             */
/*   Updated: 2024/12/18 11:51:14 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Recherche et renvoie le dernier élément de la liste chainee.
t_token	*last_element_of_list(t_token *token_list)
{
	if (!token_list)
		return (NULL);
	while (token_list->next)
		token_list = token_list->next;
	return (token_list);
}

// Attribue un type au token
int	check_token_type(char *token, t_token *last_node)
{
	if (!token)
		return (perror("error, empty token"), 0);
	if (!ft_strcmp(token, "|"))
		return (PIPE);
	else if (!ft_strcmp(token, "<"))
		return (INPUT);
	else if (!ft_strcmp(token, "<<"))
		return (HEREDOC);
	else if (!ft_strcmp(token, ">"))
		return (OUTPUT);
	else if (!ft_strcmp(token, ">>"))
		return (APPEND);
	else if (!last_node || last_node->type == PIPE)
		return (CMD);
	else
		return (ARG);
}

static char	*remove_quotes(char *token)
{
	int		i;
	char	*result;
	char	quote_type;

	result = ft_calloc(ft_strlen(token) + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	while (token && token[++i])
	{
		if (token[i] == '"' || token[i] == '\'')
		{
			quote_type = token[i++];
			while (token[i] && token[i] != quote_type)
				result = free_and_strcharjoin(&result, token[i++]);
		}
		else
			result = free_and_strcharjoin(&result, token[i]);
	}
	return (result);
}

// Ajoute un noeud a la fin de notre token_list.
void	append_node_to_token_list(t_global **global, char *prompt)
{
	t_token	*to_append;
	t_token	*last_node;

	if (!global)
		return (perror("error, empty global structure"));
	to_append = ft_calloc(1, sizeof(t_token));
	if (!to_append)
		return (perror("error, tokenization failed"));
	to_append->token = remove_quotes(prompt);
	last_node = last_element_of_list((*global)->token_list);
	to_append->type = check_token_type(to_append->token, last_node);
	if (!(*global)->token_list)
	{
		(*global)->token_list = to_append;
		to_append->index = 1;
		to_append->prev = NULL;
	}
	else
	{
		last_node->next = to_append;
		to_append->prev = last_node;
		to_append->index = last_node->index + 1;
	}
}
