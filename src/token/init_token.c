/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:03:08 by jchen             #+#    #+#             */
/*   Updated: 2024/10/15 15:30:02 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Ajoute un noeud a la fin de notre liste chainee de token.
void	append_token_node(t_token **token_list, char *prompt)
{
	t_token	*token_to_append;
	t_token	*last_node;

	if (!token_list)
		return ;
	token_to_append = malloc(sizeof(t_token));
	if (!token_to_append)
		return ;
	token_to_append->next = NULL;
	token_to_append->token = ft_strdup(prompt);
	token_to_append->type = token_type(prompt);
	if (!(*token_list))
	{
		*token_list = token_to_append;
		token_to_append->index = 1;
		token_to_append->prev = NULL;
	}
	else
	{
		last_node = last_element(*token_list);
		last_node->next = token_to_append;
		token_to_append->prev = last_node;
		token_to_append->index = last_node->index + 1;
	}
}
