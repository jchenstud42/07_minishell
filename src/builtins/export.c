/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:32:12 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/28 11:53:28 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	export_no_arg(t_env *env)
{
	char	env_tab;
	int		i;
	int		j;

	env_tab = get_env(env); //FONCTION A FINIR
	if (!env_tab)
		return (0);
	sort_env(env_tab); //FONCTION A CREER
	i = 0;
	while (env_tab[i])
	{
		j = 0;
		ft_printf("declare -x ");
		while (env_tab[i][j] && env[i][j] != '\n')
		{
			ft_printf("%s", env_tab[i][j])
			j++;
		}
		if ()
	}
}