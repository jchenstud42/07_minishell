/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:37:11 by jchen             #+#    #+#             */
/*   Updated: 2024/12/16 16:14:18 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	if (access(token, F_OK) == -1)
		return (false);
	if (access(token, X_OK) == 0)
		return (false);
	while (token[++i])
	{
		if ((token[i] != '.' && token[i] != '/'))
			return (false);
		if ((token[i] == '.' && token[i + 1] == '.' && token[i + 2] == '.'))
			return (false);
		if ((token[i] == '.' && token[i + 1] == '/'))
			break ;
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	global->exit_value = 126;
	return (true);
}

bool	pipe_after_pipe(t_global *global, t_token *token_list)
{
	if (token_list->type == PIPE && token_list->next
		&& token_list->next->type == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 2);
		return (global->exit_value = 2, true);
	}
	return (false);
}
