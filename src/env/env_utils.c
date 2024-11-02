/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:47:25 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/02 11:03:22 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	env_add_node(t_env **env, t_env *value)
{
	t_env	*tmp;

	if (*env)
	{
		tmp = find_last_node_env(*env);
		tmp->next = value;
	}
	else
		*env = value;
}

t_env	*find_last_node_env(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

int	check_env_line(t_env **env, char *line)
{
	int		i;
	int		j;
	t_env	*tmp;

	if (!env || !line)
		return (0);
	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	j = 0;
	tmp = env;
	if (!ft_strcmp(tmp->line, line, i) && (tmp->line[i] == '\0'
			|| tmp->line[i] == '='))
		return (j);
	tmp = tmp->next;
	j++;
	while (tmp != NULL)
	{
		if (!ft_strcmp(tmp->line, line, i) && (tmp->line[i] == '\0'
				|| tmp->line[i] == '='))
			return (j);
		tmp = tmp->next;
		j++;
	}
	return (-1);
}
