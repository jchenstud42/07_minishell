/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:32:46 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/30 12:03:12 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_swap_tab(int i, int j, char **tab)
{
	char	*tmp;

	tmp = tab[i];
	tab[i] = tab[j];
	tab[j] = tmp;
}

int	env_len(t_env *env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env->next == NULL)
	{
		i++;
		env = env->next;
	}
	return (i);
}
