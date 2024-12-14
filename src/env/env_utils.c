/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:01:54 by rbouquet          #+#    #+#             */
/*   Updated: 2024/12/14 12:24:36 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	env_add_node(t_env **env, char *value)
{
	t_env	*new_node;
	t_env	*tmp;

	if (!env || !value)
		return (1);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (1);
	new_node->env = ft_strdup(value);
	if (!new_node->env)
	{
		free(new_node);
		return (1);
	}
	init_env(new_node);
	new_node->next = NULL;
	if (*env)
	{
		tmp = find_last_node_env(*env);
		if (tmp)
			tmp->next = new_node;
	}
	else
		*env = new_node;
	return (0);
}

t_env	*find_last_node_env(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

int	check_env_line_exist(t_env *env, char *line)
{
	int		i;
	int		j;
	t_env	*tmp;

	if (!env || !line)
		return (-1);
	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	tmp = env;
	j = 0;
	while (tmp)
	{
		if (!ft_strncmp(tmp->env, line, i) && tmp->env[i] == '=')
			return (j);
		tmp = tmp->next;
		j++;
	}
	return (-1);
}

static char	*update_env_preparation(t_env **env, char *line, int *index)
{
	char	*temp;

	if (!line || !env || !*env)
		return (NULL);
	*index = check_env_line_exist(*env, line);
	temp = ft_strdup(line);
	if (!temp)
		return (NULL);
	return (temp);
}

int	update_env(t_env **env, char *line)
{
	int		index;
	int		i;
	char	*new_value;
	t_env	*tmp;

	new_value = update_env_preparation(env, line, &index);
	if (new_value && index >= 0)
	{
		tmp = *env;
		i = 0;
		while (i++ < index && tmp)
			tmp = tmp->next;
		if (tmp)
		{
			if (!new_value)
				return (1);
			free(tmp->env);
			tmp->env = new_value;
			// tmp->value = ;
			// tmp->name = ;
		}
	}
	else if (new_value && env_add_node(env, new_value))
		return (free(new_value), 0);
	else if (new_value)
		return (free(new_value), 1);
	return (0);
}
