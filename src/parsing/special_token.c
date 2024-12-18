/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:34:18 by jchen             #+#    #+#             */
/*   Updated: 2024/12/18 09:23:49 by rbouquet         ###   ########.fr       */
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
		|| !ft_strcmp("env", cmd) || !ft_strcmp("exit", cmd) || !ft_strcmp("$?",
			cmd))
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

bool	token_is_special_token(t_token *token)
{
	if (token->type == OUTPUT || token->type == APPEND || token->type == HEREDOC
		|| token->type == INPUT || token->type == PIPE)
		return (true);
	return (false);
}

// Verifie si le token est autre chose qu'un ARG
int	str_is_special_token(char *token)
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
			return (OUTPUT);
	}
	return (0);
}
