/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:44:15 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/16 12:52:14 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	unset_syntaxe(char *line)
{
	int	i;

	i = 0;
	if (line[0] != '_' || !ft_isalpha(line[0]))
		return (1);
	while (line[i])
	{
		if (line[i] != '_' && !ft_isalnum(line[i]))
			return (1);
		i++;
	}
	return (0);
}

int	env_exist(t_env *env, char *line)
{
	int		i;
	int		j;
	t_env	*tmp;

	tmp = env;
	if (!tmp)
		return (1);
	i = 0;
	j = 0;
	while (line[i])
		i++;
	while (tmp)
	{
		if (!ft_strncmp(tmp->env, line, i))
			return (j);
		tmp = tmp->next;
		j++;
	}
	return (1);
}
