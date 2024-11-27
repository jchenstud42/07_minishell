/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/11/23 14:03:59 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/27 10:27:30 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


// Verifie si le dernier token de notre liste est une redirection
bool	last_token_redirection(t_token *token_list)
{
	t_token *last_node;

	if (!token_list)
		return (false);
	last_node = last_element_of_list(token_list);
	if (last_node->index == 1)
		return (false);
	if (token_is_redirection(last_node))
		return (true);
	return (false);
}

// Verifie si une redirection est suivie par une redirection
bool	invalid_redirection(t_token *token_list, t_global *global)
{
	if (!token_list | !global)
		return (false);
	if (token_list->next && token_list->type == INPUT
		&& token_list->next->type == TRUNC)
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			2);
	else if (token_list->next && token_is_redirection(token_list)
		&& token_is_redirection(token_list->next))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(token_list->next->token, 2);
		ft_putstr_fd("'\n", 2);
	}
	else if (last_token_redirection(token_list))
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			2);
	else
		return (false);
	return (global->exit_value = 2, true);
}

bool	token_is_redirection(t_token *token)
{
	if (token->type == APPEND || token->type == TRUNC || token->type == HEREDOC
		|| token->type == INPUT)
		return (true);
	return (false);
}

// Verifie si l'element est une redirection (INPUT, HEREDOC, TRUNC, APPEND)
bool	str_is_redirection(char *str)
{
	if (!ft_strcmp(str, "<") || !ft_strcmp(str, "<<") || !ft_strcmp(str, ">")
		|| !ft_strcmp(str, ">>"))
		return (true);
	return (false);
}
