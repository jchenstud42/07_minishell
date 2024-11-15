/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:03:31 by jchen             #+#    #+#             */
/*   Updated: 2024/06/08 14:07:09 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putunsigned(unsigned int n, int fd)
{
	unsigned long	temp;

	temp = n;
	if (temp <= 9)
		ft_putchar_fd(temp + '0', fd);
	else
	{
		ft_putunsigned(temp / 10, fd);
		ft_putunsigned(temp % 10, fd);
	}
}

int	ft_printunsigned(unsigned int n)
{
	int				i;
	unsigned long	nbr;

	i = 1;
	nbr = n;
	while (nbr > 9)
	{
		nbr /= 10;
		i++;
	}
	ft_putunsigned(n, 1);
	return (i);
}
