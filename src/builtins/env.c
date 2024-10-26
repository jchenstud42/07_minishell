/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:31:52 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/26 15:34:39 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (!tmp)
		return (1);
	if (ft_strchr(tmp->value, '='))
		ft_printf("%s\n", tmp->value);
	tmp = tmp->next;
	while (tmp != env)
	{
		if (ft_strchr(tmp->value, '='))
			ft_printf("%s\n", tmp->value);
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
