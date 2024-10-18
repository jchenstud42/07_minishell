/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:43:18 by jchen             #+#    #+#             */
/*   Updated: 2024/10/18 12:10:42 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Rassemble les differents messages d'erreur
void	error_handler(int nb, t_global *global_data)
{
	free_all(global_data);
	if (nb == TOKENIZATION_FAILED)
		ft_printf("Error, problem with tokenization");
	exit(EXIT_FAILURE);
}
