/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:35:13 by jchen             #+#    #+#             */
/*   Updated: 2024/09/04 15:13:35 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Verifie si la string contient des caracteres imprimables.
int	ft_isprint(int c)
{
	if ((32 <= c) && (c <= 126))
		return (1);
	return (0);
}
