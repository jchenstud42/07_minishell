/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 10:54:25 by rbouquet          #+#    #+#             */
/*   Updated: 2024/12/18 09:36:47 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_env_tab(char **env_tab)
{
	int	i;

	i = 0;
	if (!env_tab)
		return ;
	while (env_tab[i])
	{
		free(env_tab[i]);
		i++;
	}
	free(env_tab);
}

int	export_no_arg(t_env *env)
{
	char	**env_tab;
	int		i;
	int		j;

	env_tab = get_env(env);
	if (!env_tab)
		return (1);
	sort_env(env_tab, env_len(env));
	i = 0;
	while (env_tab[i])
	{
		j = 0;
		ft_printf("declare -x ");
		while (env_tab[i][j] && env_tab[i][j] != '=')
			ft_printf("%c", env_tab[i][j++]);
		if (env_tab[i][j] && env_tab[i][j] == '=')
			ft_printf("=\"%s\"\n", &env_tab[i][j + 1]);
		else
			ft_printf("\n");
		i++;
	}
	free_env_tab(env_tab);
	return (0);
}

int	export_syntaxe(char *line)
{
	int	i;

	i = 0;
	if (!line[0] || (line[0] != '_' && !ft_isalpha(line[0])))
		return (0);
	while (line[i] && line[i] != '=')
	{
		if (line[i] != '_' && !ft_isalnum(line[i]))
			return (0);
		i++;
	}
	return (1);
}
