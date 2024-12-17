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


static void	handle_export_line(t_env **env, char *line)
{
	char *equal_sign;
	int pos;
	t_env *env_cpy;

	equal_sign = ft_strchr(line, '=');
	if (equal_sign && *(equal_sign + 1))
	{
		pos = check_env_line_exist(*env, line);
		if (pos >= 0)
		{
			env_cpy = *env;
			while (pos > 0 && env_cpy)
			{
				env_cpy = env_cpy->next;
				pos--;
			}
			if (env_cpy->value)
			{
				free(env_cpy->value);
				env_cpy->value = ft_strdup(equal_sign + 1);
			}
		}
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
	int i;

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
