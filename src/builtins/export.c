/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:32:12 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/28 15:12:12 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// int	export_no_arg(t_env **env)
// {
// 	char	**env_tab;
// 	int		i;
// 	int		j;

// 	env_tab = get_env(env); //FONCTION A FINIR
// 	if (!env_tab)
// 		return (0);
// 	sort_env(env_tab); //FONCTION A CREER
// 	i = 0;
// 	while (env_tab[i])
// 	{
// 		j = 0;
// 		ft_printf("declare -x ");
// 		while (env_tab[i][j] && env_tab[i][j] != '=')
// 			ft_printf("%c", env_tab[i][j++]);
// 		if (env_tab[i][j] && env_tab[i][j] == '=')
// 			ft_printf("=\"%s\"\n", &env_tab[i][j++]);
// 		else
// 			ft_printf("\n");
// 		i++;
// 	}
// 	free(env_tab);
// 	return (1);
// }

// int	export_syntaxe(char *line)
// {
// 	int	i;

// 	i = 0;
// 	if (!line[0] || (line[0] != '_' && !ft_isalpha(line[0])))
// 		return (0);
// 	while (line[i] && line[i] != '=')
// 	{
// 		if (line[i] != '_' && ft_isalnum(line[i]))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// int	ft_export(t_env **env, char **line)
// {
// 	int	i;

// 	i = 1;
// 	if (!line[i])
// 	{
// 		if (*env && !export_no_arg((env)))
// 			return (1);
// 		return (0);
// 	}
// 	while (line[i])
// 	{
// 		if (!export_syntaxe(line[i]))
// 		{
// 			ft_printf("bash: export: '%s': invalid identifier\n", line[i]);
// 			return (1);
// 		}
// 		else if (!env_add_node(env, line[i]))
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }
