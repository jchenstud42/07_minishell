/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:41:19 by jchen             #+#    #+#             */
/*   Updated: 2024/10/19 16:44:30 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Initialise la structure global
void	init_global_struct(t_global *global)
{
	global->line = NULL;
	global->token_list->index = 0;
	global->token_list->next = NULL;
	global->token_list->prev = NULL;
	global->token_list->token = NULL;
	global->token_list->type = 0;
}
