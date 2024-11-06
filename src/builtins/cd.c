/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:34:39 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/06 11:21:51 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cd_print_error_message(char *error_msg)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

// TU ME DIRAS QUAND TU AURAS FINI CETTE FONCTION POUR QUE JE LA DECOUPE!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int	update_oldpwd(t_global *global)
{
	t_env	*tmp;
	int		i;
	char	*stock_oldpwd;

	i = 0;
	tmp = global->env_list;
	if (!tmp)
		return (1);
	while (global->env_list)
	{
		i++;
		global->env_list = global->env_list->next;
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
			update_env(&global->env_list, "OLDPWD");
	}
	else if (stock_oldpwd)
	{
		stock_oldpwd = ft_strjoin("OLD", stock_oldpwd);
		update_env(&global->env_list, stock_oldpwd);
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
	update_env(&global->env_list, pwd);
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
			return (cd_print_error_message(av[1]), 1);
		else
		{
			update_pwd(global);
			return (0);
		}
	}
	return (ft_putstr_fd("bash: cd: too many arguments\n", 2), 1);
}

int	cd_home(t_global *global)
{
	char	*home;
	int		home_path;

	home = get_env_name(global->env_list, "HOME");
	if (!home)
		return (ft_putstr_fd("bash: cd: HOME not set\n", 2), 1);
	else
	{
		home_path = chdir(home);
		if (!home_path)
			return (cd_print_error_message(home), 1);
		else
			update_pwd(global);
	}
	return (0);
}
