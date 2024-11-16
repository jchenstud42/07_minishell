/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:34:39 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/16 14:34:57 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cd_print_error_message(char *error_msg)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

int	update_oldpwd(t_global *global)
{
	t_env	*tmp;
	char	*stock_oldpwd;

	tmp = global->env_list;
	if (!tmp || !global)
		return (1);
	stock_oldpwd = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->env, "PWD=", 4) == 0)
		{
			stock_oldpwd = ft_strjoin("OLD", tmp->env);
			if (!stock_oldpwd)
				return (perror("malloc failed"), 1);
			break ;
		}
		tmp = tmp->next;
	}
	if (stock_oldpwd)
	{
		update_env(&global->env_list, stock_oldpwd);
		free(stock_oldpwd);
	}
	else
		update_env(&global->env_list, "PWD=");
	return (0);
}

void	update_pwd(t_global *global)
{
	char	path[PATH_MAX];
	char	*pwd;

	if (!global)
		return ;
	update_oldpwd(global);
	if (getcwd(path, PATH_MAX) == NULL)
		return ;
	pwd = ft_strjoin("PWD=", path);
	if (!pwd)
		return (perror("error, malloc failed"));
	update_env(&global->env_list, pwd);
	free(pwd);
}

int	ft_cd(t_global *global, char **cmd_list)
{
	int	i;
	int	new_path;

	if (!global || !cmd_list)
		return (1);
	i = 0;
	while (cmd_list[i])
		i++;
	if (i == 1)
		return (cd_home(global));
	else if (i == 2)
	{
		new_path = chdir(cmd_list[1]);
		if (new_path == -1)
			return (cd_print_error_message(cmd_list[1]), 1);
		update_pwd(global);
		return (0);
	}
	else
		return (ft_putstr_fd("bash: cd: too many arguments\n", 2), 1);
}

int	cd_home(t_global *global)
{
	char	*home;
	int		home_path;

	if (!global)
		return (1);
	home = get_env_value(global->env_list, "HOME");
	if (!home)
		return (ft_putstr_fd("bash: cd: HOME not set\n", 2), 1);
	else
	{
		home_path = chdir(home);
		if (home_path == -1)
			return (cd_print_error_message(home), 1);
		else
			update_pwd(global);
	}
	return (0);
}
