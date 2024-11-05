/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/15 15:03:08 by jchen             #+#    #+#             */
/*   Updated: 2024/11/03 15:13:30 by romain           ###   ########.fr       */
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
		return (TRUNC);
	else if (!ft_strcmp(token, ">>"))
		return (APPEND);
	else if (!last_node || last_node->type == PIPE)
		return (CMD);
	// else if ((!ft_strcmp(token, "|")) && (last_node->type == ARG
	// 		|| last_node->type == CMD))
	// return (PIPE);
	else
		return (ARG);
}

// Ajoute un noeud a la fin de notre token_list.
void	append_node_to_token_list(t_global **global, char *prompt)
{
	t_token *token_to_append;
	t_token *last_node;

	if (!global)
		return (perror("error, empty global structure"));
	token_to_append = ft_calloc(1, sizeof(t_token));
	if (!token_to_append)
		return (perror("error, tokenization failed"));
	token_to_append->token = ft_strdup(prompt);
	last_node = last_element_of_list((*global)->token_list);
	token_to_append->type = check_token_type(token_to_append->token,
			last_node);
	if (!(*global)->token_list)
	{
		(*global)->token_list = token_to_append;
		token_to_append->index = 1;
		token_to_append->prev = NULL;
	}
	else
	{
		last_node->next = token_to_append;
		token_to_append->prev = last_node;
		token_to_append->index = last_node->index + 1;
	}
	// A RETIRER PLUS TARD
	// ft_printf("[%d] Type : %d, %s\n", token_to_append->index,
	// 	token_to_append->type, token_to_append->token);
}
