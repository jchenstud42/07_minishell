/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chardup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:27:18 by jchen             #+#    #+#             */
/*   Updated: 2024/11/20 11:46:40 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_chardup(char c)
{
	char	*new_char;
	int		i;

	new_char = malloc(2 * sizeof(char));
	if (!new_char)
		return (NULL);
	i = 0;
	while (i < 1)
	{
		new_char[i] = c;
		i++;
	}
	new_char[i] = '\0';
	return (new_char);
}
