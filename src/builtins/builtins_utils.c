/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:32:46 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/06 11:45:57 by jchen            ###   ########.fr       */
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
	while (env->next == NULL)
	{
		i++;
		env = env->next;
	}
	return (i);
}

// void	execute_builtin(char *cmd, t_global *global)
// {
// 	// 	if (ft_strcmp(cmd, "cd") == 0)
// 	// 		ft_cd(global->arg);
// 	if (ft_strcmp(cmd, "echo") == 0)
// 		ft_echo(&global->arg);
// 	else if (ft_strcmp(cmd, "env") == 0)
// 		ft_env(global->env_list);
// 	// else if (ft_strcmp(cmd, "exit") == 0)
// 	// 	ft_exit(global);
// 	// else if (ft_strcmp(cmd, "export") == 0)
// 	// 	ft_export(&global->env_list, &global->arg);
// 	else if (ft_strcmp(cmd, "pwd") == 0)
// 		ft_pwd();
// 	// else if (ft_strcmp(cmd, "unset") == 0)
// 	// 	ft_unset(global->env, &global->arg);
// }

void	execute_builtin(char *cmd, t_global *global)
{
	char	**cmd_list;

	cmd_list = fill_arg_after_cmd(global->token_list);
	// 	if (ft_strcmp(cmd, "cd") == 0)
	// 		ft_cd(global->arg);
	if (ft_strcmp(cmd, "echo") == 0)
		ft_echo(cmd_list);
	else if (ft_strcmp(cmd, "env") == 0)
		ft_env(global->env_list);
	// else if (ft_strcmp(cmd, "exit") == 0)
	// 	ft_exit(global);
	// else if (ft_strcmp(cmd, "export") == 0)
	// 	ft_export(&global->env_list, &global->arg);
	else if (ft_strcmp(cmd, "pwd") == 0)
		ft_pwd();
	// else if (ft_strcmp(cmd, "unset") == 0)
	// 	ft_unset(global->env, &global->arg);
}
