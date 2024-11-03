/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:34:39 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/03 15:41:01 by romain           ###   ########.fr       */
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

void	update_pwd(t_global *global)
{
	char	*path;
	char	*pwd;

	update_oldpwd(global);
	if (getcwd(path, PATH_MAX) == NULL)
		return (1);
	pwd = ft_strjoin("PWD=", path)
	if (!pwd)
		error_handler(MALLOC_FAILED, global);
	update_env(&global->env, pwd);
	free(pwd);
	return (0);
}

// int	ft_cd(t_global *global, char *av)
// {
// 	int i;

// 	i = 0;;
// 	while (av[i])
// 		i++;
// 	if (i == 1)
// 		cd_home(global); //Fonction a coder
// 	else if (i == 2)
// 	{
		
// 	}
		
// }
