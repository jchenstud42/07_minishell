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
/*   Created: 2024/11/01 11:56:07 by jchen             #+#    #+#             */
/*   Updated: 2024/11/04 18:13:03 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Verifie si le premier token est valide
// EN VRAI PAS OBLIGATOIRE, A FINIR SI BESOIN
bool	invalid_first_token(t_global *global, t_token *token_list)
{
	if (!token_list)
		return (true);
	if (token_list->type == PIPE)
		return (ft_putstr_fd("bash: syntax error near unexpected token `|'\n",
				2), global->exit_value = 2, true);
	else if (!ft_strcmp(token_list->token, ":") || !ft_strcmp(token_list->token,
			"#"))
		return (global->exit_value = 0, true);
	else if (!ft_strcmp(token_list->token, "!"))
		return (global->exit_value = 1, true);
	return (false);
}

// Verifie si le dernier token de notre liste est une redirection
bool	last_token_redirection(t_token *token_list)
{
	t_token	*last_node;

	if (!token_list)
		return (false);
	last_node = last_element_of_list(token_list);
	if (last_node->type == INPUT || last_node->type == HEREDOC
		|| last_node->type == TRUNC || last_node->type == APPEND)
		return (true);
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
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(token, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		return (true);
	}
	return (false);
}

int	check_line(t_global *global, t_token *token_list)
{
	if (!global | !token_list)
		return (1);
	if (invalid_first_token(global, token_list))
		return (1);
	else if (last_token_redirection(token_list))
		return (ft_putstr_fd("bash: syntax error near unexpected token `newline'\n",
				2), 1);
	else if (slash_in_cmd_token(token_list->token, false))
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(token_list->token, 2);
		return (ft_putstr_fd(": No such file or directory\n", 2), 1);
	}
	else
		return (0);
}
