/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:37:14 by jchen             #+#    #+#             */
/*   Updated: 2024/10/22 19:21:33 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Libere la memoire allouee a la token_list
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

// Libere toute la memoire allouee
void	free_all(t_global *global_data)
{
	if (global_data->token_list)
		free_token_list(&global_data->token_list);
	if (global_data->line)
		free(global_data->line);
	if (global_data)
		free(global_data);
}
