/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:45:23 by jchen             #+#    #+#             */
/*   Updated: 2024/09/26 11:44:16 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Cette fonction permet de copier un bloc de mémoire spécifié par
le paramètre source, et dont la taille est spécifiée via le paramètre size,
dans un nouvel emplacement désigné par le paramètre destination.
Il est bien entendu qu'il est de votre responsabilité d'allouer
suffisamment de mémoire pour le bloc de destination afin qu'il puisse
contenir toutes les données.
*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*temp_dest;
	unsigned char	*temp_src;
	size_t			i;

	i = 0;
	if ((dest == NULL) && (src == NULL))
		return (dest);
	temp_dest = (unsigned char *)dest;
	temp_src = (unsigned char *)src;
	while (i < n)
	{
		temp_dest[i] = temp_src[i];
		i++;
	}
	return (dest);
}
