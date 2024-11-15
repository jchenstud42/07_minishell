/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:16:10 by jchen             #+#    #+#             */
/*   Updated: 2024/09/04 15:13:50 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Permet de transformer une chaîne de caractères,
// représentant une valeur entière, en une valeur numérique de type int
// puis retourne celle-ci.
int	ft_atoi(const char *s)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (((9 <= s[i]) && (s[i]) <= 13) || (s[i] == 32))
		i++;
	if ((s[i] == '+') || (s[i] == '-'))
	{
		if (s[i] == '+')
			i++;
		else
		{
			sign *= -1;
			i++;
		}
	}
	while (('0' <= s[i]) && (s[i] <= '9'))
	{
		res = (res * 10) + (s[i] - '0');
		i++;
	}
	return (res * sign);
}
