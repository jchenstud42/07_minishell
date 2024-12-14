/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/30 14:02:48 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/23 13:14:30 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	env_exist_export(t_env *env, char *cmd)
{
	int		i;
	int		j;
	t_env	*tmp;

	tmp = env;
	if (!tmp)
		return (-1);
	i = 0;
	j = 0;
	while (cmd[i] != '=')
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

static void	handle_export_line(t_env **env, char *line)
{
	char	*equal_sign;
	int		pos;
	t_env	*env_cpy;

	env_cpy = *env;
	equal_sign = ft_strchr(line, '=');
	if (equal_sign)
	{
		pos = env_exist_export(*env, line);
		if (pos >= 0)
		{
			while (pos > 0)
			{
				env_cpy = env_cpy->next;
				pos--;
			}
			free(env_cpy->value);
			env_cpy->value = ft_strdup(equal_sign + 1);
		}
		else
			update_env(env, line);
	}
}

static int	export_error(t_global *global, char *line)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("': invalid identifier\n", 2);
	global->exit_value = 1;
	return (1);
}

int	ft_export(t_global *global, t_env **env, char **line)
{
	int	i;

	i = 1;
	if (!line[i] || !line)
	{
		if (*env && !export_no_arg((*env)))
			return (1);
		return (0);
	}
	while (line[i])
	{
		if (!export_syntaxe(line[i]))
			return (export_error(global, line[i]));
		handle_export_line(env, line[i]);
		i++;
	}
	global->exit_value = 0;
	return (0);
}
