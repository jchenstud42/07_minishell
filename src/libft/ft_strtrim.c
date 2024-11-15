/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:08:02 by jchen             #+#    #+#             */
/*   Updated: 2024/05/29 11:29:42 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	to_trim(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	int		start;
	int		end;
	int		final_len;
	int		i;

	start = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	end = ft_strlen(s1) - 1;
	while (to_trim(set, s1[start]))
		start++;
	while (to_trim(set, s1[end]) && end > start)
		end--;
	final_len = (end - start);
	trim = malloc(final_len * sizeof(char) + 2);
	if (!trim)
		return (NULL);
	i = 0;
	while (i <= final_len)
		trim[i++] = s1[start++];
	trim[i] = '\0';
	return (trim);
}
