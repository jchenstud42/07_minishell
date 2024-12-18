/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:27:16 by jchen             #+#    #+#             */
/*   Updated: 2024/12/18 09:23:53 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	putstr_syntax_error(void)
{
	ft_putstr_fd("minishell: syntax error near ", 2);
	ft_putstr_fd("unexpected token `newline'\n", 2);
}

// Verifie si le dernier token de notre liste est une redirection
bool	last_token_redirection(t_token *token_list)
{
	t_token	*last_node;

	if (!token_list)
		return (false);
	last_node = last_element_of_list(token_list);
	if (last_node->index == 1)
		return (false);
	if (tok_is_redir(last_node))
		return (true);
	return (false);
}

// Verifie si une redirection est suivie par une redirection
bool	invalid_redirection(t_token *token, t_global *global)
{
	if (!token | !global)
		return (false);
	if (token->next && token->type == INPUT && token->next->type == OUTPUT)
		putstr_syntax_error();
	else if (token->next && tok_is_redir(token) && tok_is_redir(token->next))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(token->next->token, 2);
		ft_putstr_fd("'\n", 2);
	}
	else if (last_token_redirection(token))
		putstr_syntax_error();
	else
		return (false);
	return (global->exit_value = 2, true);
}

bool	tok_is_redir(t_token *token)
{
	if (token->type == OUTPUT || token->type == APPEND || token->type == HEREDOC
		|| token->type == INPUT)
		return (true);
	return (false);
}

// Verifie si l'element est une redirection (INPUT, HEREDOC, APPEND, OUTPUT)
bool	str_is_redirection(char *str)
{
	if (!ft_strcmp(str, "<") || !ft_strcmp(str, "<<") || !ft_strcmp(str, ">")
		|| !ft_strcmp(str, ">>"))
		return (true);
	return (false);
}
