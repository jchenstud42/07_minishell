/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/11/20 11:51:45 by jchen             #+#    #+#             */
/*   Updated: 2024/11/20 17:20:31 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	invalid_first_token_2(t_global *global, t_token *token_list)
{
	if (!ft_strcmp(token_list->token, "&") || !ft_strcmp(token_list->token, ";")
		|| !ft_strcmp(token_list->token, ")"))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putchar_fd(token_list->token[0], 2);
		ft_putstr_fd("'\n", 2);
		return (global->exit_value = 2, true);
	}
	else if (!ft_strncmp(token_list->token, "&&", 2)
		|| !ft_strncmp(token_list->token, ";;", 2)
		|| !ft_strncmp(token_list->token, "))", 2))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `&&'\n", 2);
		return (global->exit_value = 2, true);
	}
	return (false);
}

// Verifie si le premier token est valide
bool	invalid_first_token(t_global *global, t_token *token_list)
{
	if (!token_list)
		return (false);
	if (token_list->type == PIPE)
	{
		if (token_list->next && token_list->next->token[0] == '|')
			ft_putstr_fd("minishell: syntax error near unexpected token `||'\n",
				2);
		else
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
				2);
		return (global->exit_value = 2, true);
	}
	else if (!ft_strcmp(token_list->token, ":"))
		return (global->exit_value = 0, true);
	else if (!ft_strcmp(token_list->token, "#"))
		return (global->exit_value = 0, true);
	else if (!ft_strcmp(token_list->token, "!"))
		return (global->exit_value = 1, true);
	else if (invalid_first_token_2(global, token_list))
		return (global->exit_value = 2, true);
	return (false);
}

// Verifie s'il y a un '/' dans notre token CMD, si oui
// on verifie si c'est le chemin absolu d'une commande, ou sinon
// c'est considéré comme une erreur
bool	slash_in_cmd_token(char *token, bool print_msg)
{
	if (ft_strchr(token, '/'))
	{
		if (!access(token, X_OK))
			return (false);
		if (print_msg == true)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(token, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		return (true);
	}
	return (false);
}

bool	is_point_and_slash(char *token, t_global *global)
{
	int	i;

	i = -1;
	while (token[++i])
	{
		if ((token[i] != '.' && token[i] != '/') || (token[i] == '.' && token[i
				+ 1] == '.' && token[i + 2] == '.'))
			return (false);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	global->exit_value = 126;
	return (true);
}

int	check_line(t_global *global, t_token *token_list)
{
	if (!global | !token_list)
		return (1);
	if (invalid_first_token(global, token_list)
		|| invalid_redirection(token_list, global)
		|| is_point_and_slash(token_list->token, global))
		return (1);
	// else if (slash_in_cmd_token(token_list->token, false))
	// {
	// 	ft_putstr_fd("minishell: ", 2);
	// 	ft_putstr_fd(token_list->token, 2);
	// 	global->exit_value = 127;
	// 	return (ft_putstr_fd(": No such file or directory\n", 2), 1);
	// }
	else if (slash_in_cmd_token(token_list->token, false))
		return (1);
	else
		return (0);
}
