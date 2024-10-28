/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:47:25 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/28 14:47:40 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	env_add_node(t_env **env, char *value)
{
	t_env	*node;
	t_env	*last_node;

	if (!env)
		return (0);
	node = malloc(sizeof(t_env));
	if (!node)
		return (0);
	node->line = ft_strup(value);
	if (!node->line)
		return (0);
	last_node = find_last_node_env(*env);
	node->prev = last_node;
	last_node->next = node;
	return (1);
}

int	find_last_node(t_env *env)
{
	if (!env)
		return (1);
	while (env->next)
		env = env->next;
	return (env);
}