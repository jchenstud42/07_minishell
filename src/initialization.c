/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:41:19 by jchen             #+#    #+#             */
/*   Updated: 2024/11/01 17:22:26 by jchen            ###   ########.fr       */
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

// Initialise notre tableau de tableau de commandes (char ***)
char	***init_cmd_double_array(t_global *global)
{
	int		nbr_cmd;
	char	***cmd_arrays;

	if (!global)
		error_handler(STRUCT_NOT_INITIALIZED, global);
	nbr_cmd = count_cmd_token(global->token_list);
	cmd_arrays = ft_calloc((nbr_cmd + 1), sizeof(char **));
	if (!cmd_arrays)
	{
		free(cmd_arrays);
		error_handler(MALLOC_FAILED, global);
	}
	return (cmd_arrays);
}
