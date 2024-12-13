/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:44:15 by rbouquet          #+#    #+#             */
/*   Updated: 2024/12/13 11:27:13 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	validate_unset_cmd(char *cmd)
{
	int	i;

	if (!cmd || !(*cmd))
	{
		ft_printf("minishell: unset: `%s': not a valid identifier\n", cmd);
		return (1);
	}
	else if (cmd[0] != '_' && !ft_isalpha(cmd[0]))
	{
		ft_printf("minishell: unset: `%s': not a valid identifier\n", cmd);
		return (1);
	}
	i = 0;
	while (cmd[i] && cmd[i] != '=')
	{
		if ((cmd[i] != '_' && !ft_isalnum(cmd[i])))
			return (ft_printf("minishell: unset: `%s': not a valid identifier\n",
					cmd), 1);
		i++;
	}
	if (cmd[i] == '=')
		return (ft_printf("minishell: unset: `%s': not a valid identifier\n",
				cmd), 1);
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
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->env, cmd, i) && (tmp->env[i] == '='
				|| tmp->env[i] == '\0'))
			return (j);
		tmp = tmp->next;
		j++;
	}
	return (-1);
}

void	remove_env_entry(t_env **env, int exist)
{
	t_env	*tmp;
	t_env	*next_env;
	t_env	*prev_env;
	int		j;

	tmp = *env;
	prev_env = NULL;
	j = 0;
	while (j++ < exist)
	{
		prev_env = tmp;
		tmp = tmp->next;
	}
	next_env = tmp->next;
	free(tmp->env);
	free(tmp->name);
	free(tmp->value);
	free(tmp);
	if (prev_env)
		prev_env->next = next_env;
	else
		*env = next_env;
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
		return (1);
	remove_env_entry(env, exist);
	i++;
	return (0);
}

int	ft_unset(t_global *global, t_env **env, char **cmd)
{
	int	i;

	i = 1;
	global->exit_value = 0;
	while (cmd[i])
	{
		if (unset(env, cmd[i]))
			return (1);
		i++;
	}
	return (0);
}
