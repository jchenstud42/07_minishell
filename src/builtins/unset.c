/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:44:15 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/15 11:28:09 by rbouquet         ###   ########.fr       */
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
		if (line[i] == '_' || ft_isalnum(line[i]))
			return (1);
		i++;
	}
	return (0);
}

int	unset(t_env **env, char *av)
{
	int		index;
	int		i;
	t_env	*tmp;

	if (!av || !*av)
		return (1);
	if (!unset_syntaxe(av))
		return (1);
	index = check_env_line_exist(*env, av);
	if (index == -1)
		return (1);
	tmp = *env;
	i = 0;
	while (i++ < index)
		tmp = tmp->next;
	if (tmp->prev != NULL)
		tmp->prev->next = tmp->next;
	if (tmp->next != NULL)
		tmp->next->prev = tmp->prev;
	if (tmp == *env)
		*env = tmp->next;
	free(tmp->env);
	free(tmp);
	tmp = NULL;
	return (1);
}

int	ft_unset(t_env **env, char **args)
{
	int	exit_code;
	int	i;

	exit_code = 0;
	i = 0;
	while (args[i])
	{
		if (unset(env, args[i]))
			exit_code = 1;
		i++;
	}
	return (exit_code);
}
