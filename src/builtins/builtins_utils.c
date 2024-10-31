/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:32:46 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/31 13:16:58 by rbouquet         ###   ########.fr       */
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

int	choose_builtins(char **cmd)
{
	if (cmd == NULL || *cmd == NULL)
		return (0);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (2);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (3);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (4);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (5);
	else if (ft_strcmp(cmd[0], "env") == 0 && cmd[1] == NULL)
		return (6);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (7);
	return (0);
}
