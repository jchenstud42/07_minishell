/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:47:11 by jchen             #+#    #+#             */
/*   Updated: 2024/09/04 15:29:04 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	int		i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] != c) && ((s[i + 1] == c) || (s[i + 1] == '\0')))
			count++;
		i++;
	}
	return (count);
}

static int	safe_malloc(char **array_words, int pos, size_t len)
{
	int	i;

	array_words[pos] = malloc(len * sizeof(char));
	if (array_words[pos] == NULL)
	{
		i = 0;
		while (i < pos)
		{
			free(array_words[i]);
			i++;
		}
		free(array_words);
		return (1);
	}
	return (0);
}

static int	fill(char **array_words, char const *s, char c, int word)
{
	size_t	len;
	int		idx_words;
	int		idx_s;

	idx_words = 0;
	idx_s = 0;
	while (idx_words < word)
	{
		while (s[idx_s] && s[idx_s] == c)
			idx_s++;
		len = 0;
		while (s[idx_s + len] && s[idx_s + len] != c)
			len++;
		if (len != 0)
		{
			if (safe_malloc(array_words, idx_words, len + 1))
				return (1);
		}
		ft_strlcpy(array_words[idx_words], &s[idx_s], len + 1);
		idx_words++;
		idx_s += len;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	word;
	char	**array_words;

	if (s == NULL)
		return (NULL);
	word = count_words(s, c);
	array_words = malloc((word + 1) * sizeof(char *));
	if (array_words == NULL)
		return (NULL);
	array_words[word] = NULL;
	if (fill(array_words, s, c, word))
		return (NULL);
	return (array_words);
}
