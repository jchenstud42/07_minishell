/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 10:05:06 by rbouquet          #+#    #+#             */
/*   Updated: 2024/12/18 09:26:13 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env(t_global *global, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (!tmp)
		return (1);
	while (tmp != NULL)
	{
		if (ft_strchr(tmp->env, '='))
			ft_printf("%s\n", tmp->env);
		tmp = tmp->next;
	}
	global->exit_value = 0;
	return (0);
}

void	check_env(t_env **env, t_env *tmp)
{
	if (tmp == (*env))
		(*env) = tmp->next;
	if (tmp->next == tmp)
		(*env) = NULL;
}

void	sort_env(char **tab, int len)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			tmp = ft_strcmp(tab[i], tab[j]);
			if (tmp > 0)
				ft_swap_tab(i, j, tab);
			j++;
		}
		i++;
	}
}
