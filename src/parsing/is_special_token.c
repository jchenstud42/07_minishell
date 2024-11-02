/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_special_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:18:10 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/02 16:07:52 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Verifie si c'est un builtin
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (1);
	if (!ft_strcmp("echo", cmd) || !ft_strcmp("cd", cmd) || !ft_strcmp("pwd",
			cmd) || !ft_strcmp("export", cmd) || !ft_strcmp("unset", cmd)
		|| !ft_strcmp("env", cmd) || !ft_strcmp("exit", cmd))
		return (0);
	return (1);
}

// Verifie si l'element est une redirection (INPUT, HEREDOC, TRUNC, APPEND)
int	is_redirection(char *str)
{
	if (!ft_strcmp(str, "<") || !ft_strcmp(str, "<<") || !ft_strcmp(str, ">")
		|| !ft_strcmp(str, ">>"))
		return (0);
	return (1);
}

// Verifie si l'element est une PIPE
int	is_pipe(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (1);
	return (0);
}

// TEST
// int	main(int ac, char **av)
// {
// 	if (ac == 2)
// 	{
// 		if (is_redirection(av[1]) || is_pipe(av[1]))
// 			ft_printf("ok\n");
// 		else
// 			ft_printf("error\n");
// 	}
// 	return (0);
// }
