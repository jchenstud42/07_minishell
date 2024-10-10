/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:04:31 by jchen             #+#    #+#             */
/*   Updated: 2024/09/04 15:23:24 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Recherche la première occurence d'une valeur typée int,
// mais interprétée en tant que char, dans un bloc de mémoire.
// Si la fonction a trouvé le caractère recherché, la fonction renvoie
// un pointeur vers sa première occurence. Si ce n'est pas le cas,
// la fonction renvoie la valeur NULL.
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return (&((void *)s)[i]);
		i++;
	}
	return (NULL);
}
