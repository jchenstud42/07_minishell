/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:25:14 by rbouquet          #+#    #+#             */
/*   Updated: 2024/12/18 10:44:03 by rbouquet         ###   ########.fr       */
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

static bool	is_dir(char *token)
{
	int	i;
	DIR	*dir;

	i = 0;
	dir = opendir(token);
	if (dir)
	{
		if (token[i] == '.' && token[i + 1] && token[i + 1] == '/')
			return (closedir(dir), true);
		closedir(dir);
	}
	return (false);
}

bool	is_point_and_slash(char *token, t_global *global)
{
	int		i;
	bool	is_directory;

	is_directory = is_dir(token);
	i = -1;
	while (token[++i] && !is_directory)
	{
		if (token[i] != '.' && token[i] != '/')
			return (false);
		if ((token[i] == '.' && token[i + 1] == '.' && token[i + 2] == '.'))
			return (false);
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
