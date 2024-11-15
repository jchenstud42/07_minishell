/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:10:21 by jchen             #+#    #+#             */
/*   Updated: 2024/06/08 14:07:04 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putptrhex(unsigned long n)
{
	static int		i;
	unsigned long	temp;
	static char		tab_hex[] = "0123456789abcdef";

	i = 1;
	temp = n;
	if (temp >= 16)
	{
		ft_putptrhex(temp / 16);
		i++;
	}
	write(1, &tab_hex[temp % 16], 1);
	return (i);
}

int	ft_printptr(void *adr_ptr)
{
	int				i;
	unsigned long	n;

	if (adr_ptr == NULL)
		return (write(1, "(nil)", 5));
	n = (unsigned long)adr_ptr;
	i = ft_printstr("0x");
	i += ft_putptrhex(n);
	return (i);
}
