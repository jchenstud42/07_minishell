/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:49:36 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/11 17:49:24 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strchr_env_name(char *src, char *dest)
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
		if (strcmp(find_env->name, name_env) == 0)
			return (find_env->value);
		find_env = find_env->next;
	}
	return (NULL);
}
