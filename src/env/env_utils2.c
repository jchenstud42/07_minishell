/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:49:36 by rbouquet          #+#    #+#             */
/*   Updated: 2024/12/16 10:06:43 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strchr_env_name(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '=')
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != '=')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*get_env_value(t_env *find_env, char *name_env)
{
	while (find_env)
	{
		if (ft_strcmp(find_env->name, name_env) == 0)
			return (find_env->value);
		find_env = find_env->next;
	}
	return (NULL);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*temp;
	size_t	i;

	if (!s)
		return (NULL);
	temp = malloc((n + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		temp[i] = s[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
