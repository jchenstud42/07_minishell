/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:13:53 by jchen             #+#    #+#             */
/*   Updated: 2024/09/04 15:15:59 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Calcule la longueur d'un int.
static int	ft_intlen(long n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

// Converti un int en son equivalent ASCII.
static void	ft_convert(char *str, long nbr, int *i)
{
	if (nbr / 10 != 0)
		ft_convert(str, (nbr / 10), i);
	str[*i] = (nbr % 10) + 48;
	(*i)++;
}

// Permet de transformer une valeur numerique de type int
// en une chaine de caracteres, puis retourne celle-ci.
char	*ft_itoa(int n)
{
	int		i;
	int		len;
	char	*res;
	long	nbr;

	nbr = n;
	len = ft_intlen(nbr);
	i = 0;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	if (nbr < 0)
	{
		res[i] = '-';
		nbr = -nbr;
		i++;
	}
	ft_convert(res, nbr, &i);
	res[i] = '\0';
	return (res);
}
