/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:57:47 by jchen             #+#    #+#             */
/*   Updated: 2024/06/08 14:06:57 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_puthex(unsigned int n, char c)
{
	unsigned long	temp;
	static char		tab_hex[] = "0123456789abcdef";
	static char		tab_hexup[] = "0123456789ABCDEF";

	temp = n;
	if (temp >= 16)
		ft_puthex(temp / 16, c);
	if (c == 'x')
		write(1, &tab_hex[temp % 16], 1);
	if (c == 'X')
		write(1, &tab_hexup[temp % 16], 1);
}

int	ft_printhex(unsigned int n, char c)
{
	int				i;
	unsigned long	nbr;

	i = 1;
	nbr = n;
	while (nbr >= 16)
	{
		nbr /= 16;
		i++;
	}
	ft_puthex(n, c);
	return (i);
}
