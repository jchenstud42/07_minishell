/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:32:20 by rbouquet          #+#    #+#             */
/*   Updated: 2024/12/16 17:22:07 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(t_global *global)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX))
		printf("%s\n", pwd);
	else
	{
		global->exit_value = 1;
		ft_putstr_fd("pwd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		return (ft_putstr_fd("No such file or directory\n", 2), 1);
	}
	global->exit_value = 0;
	return (0);
}
