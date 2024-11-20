/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:44:15 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/20 15:35:18 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	validate_unset_cmd(char *cmd)
{
	int	i;

	if (!cmd || !(*cmd))
	{
		ft_printf("unset: invalid identifier\n");
		return (1);
	}
	else if (cmd[0] != '_' && !ft_isalpha(cmd[0]))
	{
		ft_printf("unset: invalid identifier\n");
		return (1);
	}
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != '_' && !ft_isalnum(cmd[i]))
		{
			ft_printf("unset: invalid identifier\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	env_exist(t_env *env, char *cmd)
{
	int		i;
	int		j;
	t_env	*tmp;

	tmp = env;
	if (!tmp)
		return (-1);
	i = 0;
	j = 0;
	while (cmd[i])
		i++;
	while (tmp)
	{
		if (!ft_strncmp(tmp->env, cmd, i) && tmp->env[i] == '=')
			return (j);
		tmp = tmp->next;
		j++;
	}
	return (-1);
}

void	remove_env_entry(t_env **env, int exist)
{
	t_env	*tmp;
	int		j;

	tmp = *env;
	j = 0;
	while (j++ < exist)
		tmp = tmp->next;
	free(tmp->env);
}

int	unset(t_env **env, char *cmd)
{
	int	i;
	int	exist;

	i = 0;
	if (validate_unset_cmd(cmd))
		return (1);
	exist = env_exist(*env, cmd);
	if (exist == -1)
	{
		ft_printf("AAAA");
		return (1);
	}
	remove_env_entry(env, exist);
	i++;
	return (0);
}

int	ft_unset(t_env **env, char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (unset(env, cmd[i]))
			return (1);
		i++;
	}
	return (0);
}
