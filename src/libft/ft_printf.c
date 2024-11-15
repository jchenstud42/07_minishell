/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:23:17 by jchen             #+#    #+#             */
/*   Updated: 2024/09/04 15:28:50 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Mimique la fonction printf : converti le signe en la donnee demandee.
static int	ft_checkconv(const char c, va_list arg)
{
	int	i;

	i = 0;
	if (c == 'c')
		i += ft_printchar(va_arg(arg, int));
	else if (c == 's')
		i += ft_printstr(va_arg(arg, char *));
	else if (c == 'p')
		i += ft_printptr(va_arg(arg, void *));
	else if (c == 'd')
		i += ft_printnbr(va_arg(arg, int));
	else if (c == 'i')
		i += ft_printnbr(va_arg(arg, int));
	else if (c == 'u')
		i += ft_printunsigned(va_arg(arg, unsigned int));
	else if (c == 'x')
		i += ft_printhex(va_arg(arg, unsigned int), 'x');
	else if (c == 'X')
		i += ft_printhex(va_arg(arg, unsigned int), 'X');
	else if (c == '%')
	{
		ft_putchar_fd('%', 1);
		return (1);
	}
	return (i);
}

// Mimique la fonction printf.
int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	arg;

	i = 0;
	va_start(arg, str);
	while (*str != '\0')
	{
		if (*str == '%')
		{
			if (ft_strchr("cspdiuxX%", *++str))
				i += ft_checkconv(*str, arg);
		}
		else
			i += ft_printchar(*str);
		str++;
	}
	va_end(arg);
	return (i);
}
