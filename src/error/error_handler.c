/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:43:18 by jchen             #+#    #+#             */
/*   Updated: 2024/10/23 14:45:59 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Rassemble les differents messages d'erreur
void	error_handler(int error_number, t_global *global_data)
{
	free_all(global_data);
	if (error_number == TOKENIZATION_FAILED)
		ft_printf("Error, problem with tokenization.\n");
	else if (error_number == STRUCT_INIT_FAILED)
		ft_printf("Error, failed to initialize the struct.\n");
	else if (error_number == STRUCT_NOT_INITIALIZED)
		ft_printf("Error, struct isn't initialized.\n");
	else if (error_number == EMPTY_LINE)
		ft_printf("Error, empty line given to the struc.\n");
	else if (error_number == MALLOC_FAILED)
		ft_printf("Error, memory allocation failed.\n");
	else if (error_number == WRONG_TOKEN_TYPE)
		ft_printf("Error, unknown token type\n");
	exit(EXIT_FAILURE);
}
