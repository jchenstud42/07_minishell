/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:42:43 by jchen             #+#    #+#             */
/*   Updated: 2024/09/04 15:13:17 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Verifie si la string contient des caracteres ASCII.
int	ft_isascii(int c)
{
	if ((0 <= c) && (c <= 127))
		return (1);
	return (0);
}
