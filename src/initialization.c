/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:41:19 by jchen             #+#    #+#             */
/*   Updated: 2024/10/25 16:48:45 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Malloc + initilise a 0 la structure global
void	calloc_global_struct(t_global **global_data)
{
	*global_data = ft_calloc(1, sizeof(t_global));
	if (!*global_data)
		error_handler(STRUCT_INIT_FAILED, *global_data);
	(*global_data)->line = NULL;
	(*global_data)->token_list = NULL;
}
