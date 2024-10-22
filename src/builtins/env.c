/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:31:52 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/22 14:10:29 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	ft_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (!tmp)
		return (false);
	if (ft_strchr(tmp->str, '='))
		printf("%s\n", tmp->str);
	tmp = tmp->next;
	while (tmp != env)
	{
		if (ft_strchr(tmp->str, '='))
			printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
	return (true);
}

void	check_env(t_env **env, t_env *tmp)
{
	if (tmp == (*env))
		(*env) = tmp->next;
	if (tmp->next == tmp)
		(*env) = NULL;
}
