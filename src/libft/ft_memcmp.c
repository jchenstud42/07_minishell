/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:55:57 by jchen             #+#    #+#             */
/*   Updated: 2024/09/04 15:25:06 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Permet de comparer le contenu de deux blocs de mémoire spécifiés
par les deux premiers paramètres de la fonction. Le troisième paramètre, size,
permet de spécifier le nombre d'octets sur lequel comparer les deux blocs.
Les octets des deux blocs sont comparés deux à deux.
Tant que les deux octets comparés sont égaux,la fonction passe aux deux suivants.
Si les deux octets comparés sont différents, alors la fonction renvérra lequel
des deux blocs est le plus petit en termes de contenu.

Trois cas sont possibles en termes de valeur de retour.
Soit la valeur de retour est négative : dans ce cas, le premier octet
qui différe entre les deux blocs est plus petit dans le premier bloc.
Soit la valeur de retour est nulle : dans ce cas,
les deux blocs ont leurs contenus strictement identique.
Enfin, si la valeur de retour est positive : dans ce cas, le premier octet
qui différe entre les deux blocs est plus grand dans le premier bloc.
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((i < n - 1)
		&& (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i]))
	{
		i++;
	}
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
