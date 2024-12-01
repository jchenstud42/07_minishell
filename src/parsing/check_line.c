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


static bool	invalid_first_token_2(t_token *token_list)
{
	if (!ft_strcmp(token_list->token, "&") || !ft_strcmp(token_list->token, ";")
		|| !ft_strcmp(token_list->token, ")"))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putchar_fd(token_list->token[0], 2);
		ft_putstr_fd("'\n", 2);
		return (true);
	}
	else if (!token_list->next && str_is_redirection(token_list->token))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			2);
		return (true);
	}
	else if (!ft_strncmp(token_list->token, "&&", 2)
		|| !ft_strncmp(token_list->token, ";;", 2)
		|| !ft_strncmp(token_list->token, "))", 2))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putchar_fd(token_list->token[0], 2);
		ft_putchar_fd(token_list->token[1], 2);
		ft_putstr_fd("'\n", 2);
		return (true);
	}
	return (false);
}

// Verifie si le premier token est valide
bool	invalid_first_token(t_global *global, t_token *token_list)
{
	if (!token_list)
		return (false);
	else if (token_list->token[0] == '\0')
	{
		ft_putstr_fd("minishell: : command not found\n", 2);
		return (global->exit_value = 127, true);
	}
	else if (pipe_after_pipe(global, token_list))
		return (true);
	else if (token_list->type == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (global->exit_value = 2, true);
	}
	else if (!ft_strcmp(token_list->token, ":"))
		return (global->exit_value = 0, true);
	else if (!ft_strcmp(token_list->token, "#"))
		return (global->exit_value = 0, true);
	else if (!ft_strcmp(token_list->token, "!"))
		return (global->exit_value = 1, true);
	else if (invalid_first_token_2(token_list))
		return (global->exit_value = 2, true);
	return (false);
}

bool	check_in_first_token(t_global *global, t_token *token_list)
{
	if (invalid_first_token(global, token_list)
		|| is_point_and_slash(token_list->token, global))
		return (true);
	else if (slash_in_cmd_token(token_list->token, false))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token_list->token, 2);
		global->exit_value = 127;
		return (ft_putstr_fd(": No such file or directory\n", 2), true);
	}
	return (false);
}

int	check_line(t_global *global, t_token *token_list)
{
	t_token *temp_token;

	if (!global | !token_list)
		return (1);
	else if (check_in_first_token(global, token_list))
		return (1);
	temp_token = token_list;
	while (temp_token)
	{
		if (token_is_special_token(temp_token))
		{
			if (invalid_redirection(temp_token, global))
				return (1);
		}
		if (pipe_after_pipe(global, temp_token))
			return (1);
		temp_token = temp_token->next;
	}
	return (0);
}
