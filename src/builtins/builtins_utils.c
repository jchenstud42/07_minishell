/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/30 11:32:46 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/08 15:10:07 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_swap_tab(int i, int j, char **tab)
{
	char	*tmp;

	tmp = tab[i];
	tab[i] = tab[j];
	tab[j] = tmp;
}

int	env_len(t_env *env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void	execute_builtin(t_cmd *cmd_list, t_global *global)
{
	if (ft_strcmp(cmd_list->cmd, "cd") == 0)
		ft_cd(global, cmd_list->cmd_args);
	else if (ft_strcmp(cmd_list->cmd, "echo") == 0)
		ft_echo(cmd_list->cmd_args);
	else if (ft_strcmp(cmd_list->cmd, "env") == 0)
		ft_env(global->env_list);
	else if (ft_strcmp(cmd_list->cmd, "export") == 0)
		ft_export(&global->env_list, cmd_list->cmd_args);
	else if (ft_strcmp(cmd_list->cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd_list->cmd, "unset") == 0)
		ft_unset(&global->env_list, cmd_list->cmd_args);
	else if (ft_strcmp(cmd_list->cmd, "exit") == 0)
		ft_exit(global, cmd_list->cmd_args);
}
