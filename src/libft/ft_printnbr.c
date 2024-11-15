/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:42:09 by jchen             #+#    #+#             */
/*   Updated: 2024/06/08 14:07:00 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printnbr(int n)
{
	int		i;
	long	nbr;

	i = 1;
	nbr = n;
	if (nbr < 0)
	{
		nbr *= -1;
		i++;
	}
	while (nbr > 9)
	{
		nbr /= 10;
		i++;
	}
	ft_putnbr_fd(n, 1);
	return (i);
}
