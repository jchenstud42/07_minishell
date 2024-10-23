/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:03:08 by jchen             #+#    #+#             */
/*   Updated: 2024/10/23 17:36:41 by jchen            ###   ########.fr       */
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
int	check_token_type(char *token, t_global **global)
{
	if (!token)
		error_handler(ERROR_TOKEN_TYPE_ATTRIBUTION, *global);
	if (!ft_strcmp(token, "|"))
		return (PIPE);
	if ((*global)->token_list->index == 1
		|| (*global)->token_list->prev->type == PIPE)
	{
		if (!ft_strcmp(token, "<"))
			return (INPUT);
		else if (!ft_strcmp(token, "<<"))
			return (HEREDOC);
		else if (!ft_strcmp(token, ">"))
			return (TRUNC);
		else if (!ft_strcmp(token, ">>"))
			return (APPEND);
		else
			return (CMD);
	}
	return (ARG);
}

// Ajoute un noeud a la fin de notre token_list.
void	append_node_to_token_list(t_global **global, char *prompt)
{
	t_token	*token_to_append;
	t_token	*last_node;

	if (!global)
		return ;
	token_to_append = ft_calloc(1, sizeof(t_token));
	if (!token_to_append)
		error_handler(TOKENIZATION_FAILED, *global);
	token_to_append->token = ft_strdup(prompt);
	if ((*global)->token_list == NULL)
	{
		(*global)->token_list = token_to_append;
		token_to_append->index = 1;
		token_to_append->prev = NULL;
	}
	else
	{
		last_node = last_element_of_list((*global)->token_list);
		last_node->next = token_to_append;
		token_to_append->prev = last_node;
		token_to_append->index = last_node->index + 1;
	}
	token_to_append->type = check_token_type(token_to_append->token, global);
}

// TEST
// int	main(int ac, char **av)
// {
// 	t_global	*global_data;
// 	int			ac_nbr;
// 	t_token		*current;

// 	(void)**av;
// 	global_data = NULL;
// 	calloc_global_struct(&global_data);
// 	ac_nbr = ac;
// 	while (ac_nbr-- > 1)
// 	{
// 		if (ac_nbr == 2)
// 			append_node_to_token_list(&global_data, "bonjour");
// 		else if (ac_nbr == 1)
// 			append_node_to_token_list(&global_data, "au revoir");
// 		else
// 			append_node_to_token_list(&global_data, "bla bla");
// 	}
// 	current = global_data->token_list;
// 	while (current)
// 	{
// 		ft_printf("[%d] Type : %d, %s\n", current->index, current->type,
// 			current->token);
// 		current = current->next;
// 	}
// 	free_all(global_data);
// 	return (0);
// }
