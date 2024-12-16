/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:49:36 by rbouquet          #+#    #+#             */
/*   Updated: 2024/12/16 14:54:37 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

char	*ft_strndup(const char *s, int n)
{
	char	*temp;
	int		i;

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

static int	update_env_node(t_env *tmp, char *new_env)
{
	if (!new_env)
		return (1);
	free(tmp->env);
	tmp->env = new_env;
	free(tmp->name);
	tmp->name = ft_strndup(new_env, ft_strchr(new_env, '=') - new_env);
	if (!tmp->name)
		return (1);
	free(tmp->value);
	tmp->value = ft_strdup(new_env + ft_strlen(tmp->name) + 1);
	if (!tmp->value)
		return (1);
	return (0);
}

int	update_env(t_env **env, char *line)
{
	int		index;
	char	*new_env;
	t_env	*tmp;

	new_env = update_env_preparation(env, line, &index);
	if (new_env && index >= 0)
	{
		tmp = *env;
		while (index-- && tmp)
			tmp = tmp->next;
		if (tmp && update_env_node(tmp, new_env))
			return (1);
	}
	else if (new_env && env_add_node(env, new_env))
		return (free(new_env), 0);
	else if (new_env)
		return (free(new_env), 1);
	return (0);
}
