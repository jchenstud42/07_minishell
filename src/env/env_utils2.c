/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:49:36 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/15 11:28:01 by rbouquet         ###   ########.fr       */
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
