/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:02:48 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/16 12:49:34 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
			ft_printf("=\"%s\"\n", &env_tab[i][j++]);
		else
			ft_printf("\n");
		i++;
	}
	free(env_tab);
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

int	ft_export(t_env **env, char **line)
{
	int	i;

	i = 1;
	if (!line[i])
	{
		if (*env && !export_no_arg((*env)))
			return (1);
		return (0);
	}
	while (line[i])
	{
		if (!export_syntaxe(line[i]))
		{
			ft_putstr_fd("bash: export: '", 2);
			ft_putstr_fd(line[i], 2);
			ft_putstr_fd("': invalid identifier\n", 2);
			return (1);
		}
		else if (!update_env(env, line[i]))
			return (1);
		i++;
	}
	return (0);
}
