/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:09:49 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/15 15:10:41 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtins(char *cmd)
{
	if (!cmd)
		return (1);
	if (!ft_strcmp("echo", cmd) || !ft_strcmp("cd", cmd) || \
		!ft_strcmp("pwd", cmd) || !ft_strcmp("export", cmd) || \
		!ft_strcmp("unset", cmd) || !ft_strcmp("env", cmd) || \
		!ft_strcmp("exit", cmd))
		return (1);
	return (0);
}
