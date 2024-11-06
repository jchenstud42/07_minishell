/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:43:18 by jchen             #+#    #+#             */
/*   Updated: 2024/11/06 11:22:23 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Rassemble les differents messages d'erreur
void	error_handler(int error_number, t_global *global_data)
{
	free_all(global_data);
	if (error_number == TOKENIZATION_FAILED)
		ft_putstr_fd("Error, problem with tokenization.\n", 2);
	else if (error_number == STRUCT_INIT_FAILED)
		ft_putstr_fd("Error, failed to initialize the struct.\n", 2);
	else if (error_number == STRUCT_NOT_INITIALIZED)
		ft_putstr_fd("Error, struct isn't initialized.\n", 2);
	else if (error_number == EMPTY_LINE)
		ft_putstr_fd("Error, empty line given to the struc.\n", 2);
	else if (error_number == MALLOC_FAILED)
		ft_putstr_fd("Error, memory allocation failed.\n", 2);
	else if (error_number == ERROR_TOKEN_TYPE_ATTRIBUTION)
		ft_putstr_fd("Error, unknown token type\n", 2);
	else if (error_number == EXECVE_FAILED)
		ft_putstr_fd("Error, problem with execve\n", 2);
	else if (error_number == FORK_FAILED)
		ft_putstr_fd("Error, creation of the child process failed\n", 2);
	else if (error_number == DUP_FAILED)
		ft_putstr_fd("Error, process duplication failed\n", 2);
	else if (error_number == PIPE_FAILED)
		ft_putstr_fd("Error, pipe creation failed\n", 2);
	exit(EXIT_FAILURE);
}

// ON DEVRA PLUTOT UTILISER UN TRUC DU GENRE A LA FIN
//
// if (!pasbon)
// return(ft_putstr_fd("erreur je sais pas ou", 2), 1);
//
// et faire un free_all a la fin du main
