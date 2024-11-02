/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:34:39 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/02 15:59:51 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	update_oldpwd(t_global *global)
{
	t_env	*tmp;
	int		i;
	char	*stock_oldpwd;

	i = 0;
	tmp = global->env;
	if (!tmp)
		return (1);
	while (global->env)
	{
		i++;
		global->env = global->env->next;
	}
	while (i--)
	{
		if (ft_strcmp(tmp->env, "OLDPWD=") == 0)
			stock_oldpwd = tmp->env;
		tmp = tmp->next;
	}
	if (!stock_oldpwd)
	{
		if (!stock_oldpwd)
			update_env(&global->env, "OLDPWD");
	}
	else if (stock_oldpwd)
	{
		stock_oldpwd = ft_strjoin("OLD", stock_oldpwd);
		update_env(&global->env, stock_oldpwd);
	}
	free(stock_oldpwd);
	return (0);
}

// int	update_pwd(t_global *global)
// {
// 	char	*path;

// 	update_oldpwd(global);
// 	if (getcwd(path, PATH_MAX) == NULL)
// 		return (1);
// 	return (0);
// }
