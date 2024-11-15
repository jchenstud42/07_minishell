/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:45:25 by jchen             #+#    #+#             */
/*   Updated: 2024/09/04 15:12:19 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Alloue un bloc de mémoire en initialisant tous ces octets à la valeur 0.
void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*tab;
	size_t			i;

	i = 0;
	if ((nmemb * size < nmemb || nmemb * size < size) && (nmemb * size > 0))
		return (NULL);
	tab = malloc(nmemb * size);
	if (tab == 0)
		return (NULL);
	while (i < nmemb * size)
		tab[i++] = 0;
	return (tab);
}
