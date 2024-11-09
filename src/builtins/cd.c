/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:34:39 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/09 18:32:15 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// QUAND TU FAIS CD TOUT SEUL, CA DOIT TE RAMENER A $HOME (/home/rbouquet)
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
	stock_oldpwd = NULL;
	if (!tmp)
		return (1);
	while (global->env_list)
	{
		i++;
		global->env_list = global->env_list->next;
	}
	while (i--)
	{
		if (ft_strcmp(tmp->env, "PWD=") == 0)
			stock_oldpwd = tmp->env;
		tmp = tmp->next;
	}
	if (!stock_oldpwd)
			update_env(&global->env_list, "OLDPWD");
	else
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
		return (perror("error, malloc failed"));
	update_env(&global->env_list, pwd);
	free(pwd);
}

int	ft_cd(t_global *global, char **cmd_list)
{
	int	i;
	int	new_path;

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
		else
		{
			update_pwd(global);
			return (0);
		}
	}
	else
		return (ft_putstr_fd("bash: cd: too many arguments\n", 2), 1);
}

int	cd_home(t_global *global)
{
	char	*home;
	int		home_path;

	ft_printf("AAAA");
	home = get_env_name(global->env_list, "HOME");
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
