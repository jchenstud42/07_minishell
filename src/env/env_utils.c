/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:01:54 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/04 15:22:54 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	env_add_node(t_env **env, char *value)
{
	t_env	*new_node;
	t_env	*tmp;


	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (1);
	new_node->env = ft_strdup(value);
	if (!new_node->env)
	{
		free(new_node);
		return (1);
	}
	new_node->next = NULL;
	if (*env)
	{
		tmp = find_last_node_env(*env);
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

int	check_env_line(t_env *env, char *line)
{
	int		i;
	int		j;
	t_env	*tmp;

	if (!env || !line)
		return (-1);
	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	j = 0;
	tmp = env;
	if (!ft_strncmp(tmp->env, line, i) && (tmp->env[i] == '\0'
			|| tmp->env[i] == '='))
		return (j);
	tmp = tmp->next;
	j++;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->env, line, i) && (tmp->env[i] == '\0'
				|| tmp->env[i] == '='))
			return (j);
		tmp = tmp->next;
		j++;
	}
	return (-1);
}

int	update_env(t_env **env, char *line)
{
	int		index;
	int		i;
	t_env	*tmp;

	if (!line)
		return (1);
	index = check_env_line(*env, line);
	if (index >= 0)
	{
		tmp = *env;
		i = 0;
		while (i++ < index)
			tmp = tmp->next;
		free(tmp->env);
		tmp->env = ft_strdup(line);
		if (!tmp->env)
			return (1);
	}
	else if (index == -1)
	{
		if (env_add_node(env, line) != 0)
			return (1);
	}
	return (0);
}

char	*get_env_name(t_env *find_env, char	*name_env)
{
	while (find_env)
	{
		if (ft_strcmp(find_env->name, name_env) == 0)
			return (find_env->value);
		find_env = find_env->next;
	}
	return (NULL);
}
