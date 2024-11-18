/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:44:15 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/18 11:03:27 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	unset_syntaxe(char *line)
{
	int	i;

	i = 0;
	if (line[0] != '_' || !ft_isalpha(line[0]))
		return (1);
	while (line[i])
	{
		if (line[i] != '_' && !ft_isalnum(line[i]))
			return (1);
		i++;
	}
	return (0);
}

int	env_exist(t_env *env, char *line)
{
	int		i;
	int		j;
	t_env	*tmp;

	tmp = env;
	if (!tmp)
		return (1);
	i = 0;
	j = 0;
	while (line[i])
		i++;
	while (tmp)
	{
		if (!ft_strncmp(tmp->env, line, i))
			return (j);
		tmp = tmp->next;
		j++;
	}
	return (1);
}

int	ft_unset(t_env **env, char **args)
{
	int		i;
	int		j;
	int		exist;
	t_env	*tmp;

	i = 0;
	while (args[i])
	{
		if (!args[i] || !(*args[i]) || !unset_syntaxe(args[i]))
		{
			ft_printf("unset: invalid identifier\n");
			return (1);
		}
		exist = env_exist(*env, args[i]);
		if (exist == 1)
			return (1);
		tmp = *env;
		j = 0;
		while (j++ < exist)
			tmp = tmp->next;
		if (tmp->prev)
			tmp->prev->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
		if (tmp == *env)
			*env = tmp->next;
		free(tmp->env);
		free(tmp);
		tmp = NULL;
		i++;
	}
	return (0);
}
