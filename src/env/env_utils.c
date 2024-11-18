/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:01:54 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/18 13:12:03 by rbouquet         ###   ########.fr       */
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

int	update_env(t_env **env, char *line)
{
	int		index;
	int		i;
	char	*new_value;
	t_env	*tmp;

	if (!line || !env || !*env)
		return (1);
	index = check_env_line_exist(*env, line);
	new_value = ft_strdup(line);
	if (index >= 0)
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
		}
	}
	else if (env_add_node(env, new_value))
		return (free(new_value), 0);
	else
		return (free(new_value), 1);
	return (0);
}

char	**ft_env_cpy(t_env *env)
{
	t_env	*current_env;
	int		i;
	int		len;
	char	**env_tab;

	len = 0;
	current_env = env;
	while (current_env)
	{
		len++;
		current_env = current_env->next;
	}
	current_env = env;
	i = 0;
	env_tab = malloc(sizeof(char *) * (len + 1));
	if (!env_tab)
		return (NULL);
	while (current_env)
	{
		env_tab[i] = current_env->env;
		current_env = current_env->next;
		i++;
	}
	env_tab[i] = NULL;
	return (env_tab);
}
