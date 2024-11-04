/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:34:39 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/04 12:29:50 by rbouquet         ###   ########.fr       */
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
	char	path[PATH_MAX];
	char	*pwd;

	update_oldpwd(global);
	if (getcwd(path, PATH_MAX) == NULL)
		return ;
	pwd = ft_strjoin("PWD=", path);
	if (!pwd)
		error_handler(MALLOC_FAILED, global);
	update_env(&global->env, pwd);
	free(pwd);
}

int	ft_cd(t_global *global, char **av)
{
	int	i;
	int	new_path;

	i = 0;
	while (av[i])
		i++;
	if (i == 1)
		cd_home(global);
	else if (i == 2)
	{
		new_path = chdir(av[1]);
		if (!new_path)
		{
			ft_printf("bash: cd: %s: No such file or directory\n", new_path);
			return (1);
		}
		else
		{
			update_pwd(global);
			return (0);
		}
	}
	return (ft_printf("bash: cd: too many arguments\n"));
}

int	cd_home(t_global *global)
{
	char	*home;
	int		home_path;

	home = get_env_name(global->env, "HOME");
	if (!home)
	{
		write(2, "bash: cd: HOME not set\n", 23);
		return (1);
	}
	else
	{
		home_path = chdir(home);
		if (!home_path)
		{
			ft_printf("bash: cd: %s: No such file or directory\n", home_path);
			return (1);
		}
		else
			update_pwd(global);
	}
	return (0);
}
