/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:03:08 by jchen             #+#    #+#             */
/*   Updated: 2024/10/22 14:13:34 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Recherche et renvoie le dernier élément de la liste chainee.
t_token	*last_element(t_token *token_list)
{
	if (!token_list)
		return (NULL);
	while (token_list->next)
		token_list = token_list->next;
	return (token_list);
}

// Ajoute un noeud a la fin de notre liste chainee de token.
// void	append_token_node(t_global **global, char *prompt)
// {
// 	t_token	*token_to_append;
// 	t_token	*last_node;

// 	if (!global || !(*global) || !((*global)->token_list))
// 		return ;
// 	token_to_append = malloc(sizeof(t_token));
// 	if (!token_to_append)
// 		error_handler(TOKENIZATION_FAILED, global);
// 	token_to_append->next = NULL;
// 	token_to_append->token = ft_strdup(prompt);
// 	token_to_append->type = token_type(prompt);
// 	if ((*global)->token_list == NULL)
// 	{
// 		(*global)->token_list = token_to_append;
// 		token_to_append->index = 1;
// 		token_to_append->prev = NULL;
// 	}
// 	else
// 	{
// 		last_node = last_element((*global)->token_list);
// 		last_node->next = token_to_append;
// 		token_to_append->prev = last_node;
// 		token_to_append->index = last_node->index + 1;
// 	}
// }

void	append_token_node_test(t_global **global, char *prompt)
{
	// t_token	*token_to_append;
	// t_token	*last_node;
	(void)**global;
	ft_printf("%s\n", prompt);
	// (void)*prompt;
	// if (!global || !(*global) || !((*global)->token_list))
	// 	return ;
	// token_to_append = malloc(sizeof(t_token));
	// if (!token_to_append)
	// 	error_handler(TOKENIZATION_FAILED, global);
	// token_to_append->next = NULL;
	// token_to_append->token = "bonjour";
	// token_to_append->type = CMD;
	// if ((*global)->token_list == NULL)
	// {
	// 	(*global)->token_list = token_to_append;
	// 	token_to_append->index = 1;
	// 	token_to_append->prev = NULL;
	// }
	// else
	// {
	// 	last_node = last_element((*global)->token_list);
	// 	last_node->next = token_to_append;
	// 	token_to_append->prev = last_node;
	// 	token_to_append->index = last_node->index + 1;
	// }
}

// int	main(int ac, char **av)
// {
// 	t_global *global_data;
// 	int ac_nbr;

// 	(void)**av;
// 	global_data = ft_calloc(1, sizeof(t_global));
// 	if (!global_data)
// 		return (ft_printf("Error main"), 1);
// 	ac_nbr = ac;
// 	while (ac_nbr-- > 0)
// 		append_token_node_test(&global_data, "bonjour");
// 	return (0);
// }
