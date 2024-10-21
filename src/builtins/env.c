/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:31:52 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/21 10:38:56 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (!tmp)
		return (1);
	if (ft_strchr(tmp->str, "="))
		printf("%s\n", tmp->str);
	tmp = tmp->next;
	while (tmp != env)
	{
		if (ft_strchr(tmp->str, "="))
			printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
	return (0);
}

void	check_env(t_env **env, t_env *tmp)
{
	if (tmp == (*env))
		(*env) = tmp->next;
	if (tmp->next == tmp)
		(*env) = NULL;
}
