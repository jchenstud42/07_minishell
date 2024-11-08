/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:02:24 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/08 13:50:23 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**get_env(t_env *env)
{
	t_env	*env_size;
	char	**env_tab;
	int		i;

	i = 0;
	env_size = env;
	while (env_size)
	{
		i++;
		env_size = env_size->next;
	}
	env_tab = malloc(sizeof(char *) * (i + 1));
	if (!env_tab)
		return (NULL);
	env_size = env;
	i = 0;
	while (env_size)
	{
		env_tab[i] = env_size->env;
		env_size = env_size->next;
		i++;
	}
	env_tab[i] = NULL;
	return (env_tab);
}
