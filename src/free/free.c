/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:37:14 by jchen             #+#    #+#             */
/*   Updated: 2024/10/22 14:07:23 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_token_list(t_token **token_list)
{
	t_token	*temp;
	t_token	*current;

	if (!token_list)
		return ;
	current = *token_list;
	while (current)
	{
		temp = current->next;
		free(current);
		current = temp;
	}
	*token_list = NULL;
}

void	free_all(t_global *global_data)
{
	if (global_data->token_list != NULL)
		free_token_list(&global_data->token_list);
}
