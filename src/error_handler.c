/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:43:18 by jchen             #+#    #+#             */
/*   Updated: 2024/10/26 12:09:50 by rbouquet         ###   ########.fr       */
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
	else if (error_number == ERROR_TOKEN_TYPE_ATTRIBUTION)
		ft_printf("Error, unknown token type\n");
	else if (error_number == COMMAND_NOT_FOUND)
		ft_printf("Error, command not found\n");
	else if (error_number == EXECVE_FAILED)
		ft_printf("Error, problem with execve\n");
	else if (error_number == FORK_FAILED)
		ft_printf("Error, creation of the child process fail\n");
	exit(EXIT_FAILURE);
}
