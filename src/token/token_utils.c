/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:30:04 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/23 10:01:20 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// degouter, javais fais un bo truc mais apres, jai remarque que tu l'avais deja fais, gg a toi 

bool	is_white_space(char c)
{
	if (((9 <= c) && (c <= 13)) || (c == 32))
		return (TRUE);
	return (FALSE);
}