/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_special_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/25 14:18:10 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/07 18:06:10 by jchen            ###   ########.fr       */
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

// Verifie si le token est autre chose qu'un ARG
int	is_special_token(char *token)
{
	if (!token || !token[0])
		return (0);
	if (token[0] == '|')
		return (PIPE);
	else if (token[0] == '<')
	{
		if (token[1] == '<')
			return (HEREDOC);
		else
			return (INPUT);
	}
	else if (token[0] == '>')
	{
		if (token[1] == '>')
			return (APPEND);
		else
			return (TRUNC);
	}
	return (0);
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
int	is_pipe(char c)
{
	if (c == '|')
		return (1);
	return (0);
}
