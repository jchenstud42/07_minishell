/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:01:54 by rbouquet          #+#    #+#             */
/*   Updated: 2024/12/16 14:53:15 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// int	env_add_node(t_env **env, char *value)
// {
// 	t_env	*new_node;
// 	t_env	*tmp;

// 	if (!env || !value)
// 		return (1);
// 	new_node = malloc(sizeof(t_env));
// 	if (!new_node)
// 		return (1);
// 	new_node->env = ft_strdup(value);
// 	if (!new_node->env)
// 	{
// 		free(new_node);
// 		return (1);
// 	}
// 	init_env(new_node);
// 	new_node->next = NULL;
// 	if (*env)
// 	{
// 		tmp = find_last_node_env(*env);
// 		if (tmp)
// 			tmp->next = new_node;
// 		else
// 		{
// 			free(new_node->env);
// 			free(new_node);
// 			return (1);
// 		}
// 	}
// 	else
// 		*env = new_node;
// 	return (0);
// }

static int	create_env_node(t_env **new_node, char *value)
{
	*new_node = malloc(sizeof(t_env));
	if (!*new_node)
		return (1);
	(*new_node)->env = ft_strdup(value);
	if (!(*new_node)->env)
	{
		free(*new_node);
		return (1);
	}
	init_env(*new_node);
	(*new_node)->next = NULL;
	return (0);
}

int	env_add_node(t_env **env, char *value)
{
	t_env	*new_node;
	t_env	*tmp;

	if (!env || !value || create_env_node(&new_node, value))
		return (1);
	if (*env)
	{
		tmp = find_last_node_env(*env);
		if (!tmp)
		{
			free(new_node->env);
			free(new_node);
			return (1);
		}
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
