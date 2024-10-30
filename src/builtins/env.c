/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:31:52 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/30 11:31:52 by rbouquet         ###   ########.fr       */
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
