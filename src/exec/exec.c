/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:09:49 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/25 18:09:33 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Verifie si c'est un builtin
bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strcmp("echo", cmd) || !ft_strcmp("cd", cmd) || !ft_strcmp("pwd",
			cmd) || !ft_strcmp("export", cmd) || !ft_strcmp("unset", cmd)
		|| !ft_strcmp("env", cmd) || !ft_strcmp("exit", cmd))
		return (false);
	return (true);
}

// PROTOTYPE :
// On utilise execve() pour lancer la commande/verifier si c'est une
// vraie commande
void	execute_command(char *cmd, char **env)
{
	const char	*filename;
	char		*command_file;
	char		*argv[2];

	if (!cmd)
		return ;
	filename = "/usr/bin/";
	command_file = malloc(ft_strlen(filename) + ft_strlen(cmd) + 1);
	if (command_file)
	{
		ft_strlcpy(command_file, filename, ft_strlen(filename) + 1);
		ft_strlcat(command_file, cmd, ft_strlen(cmd) + ft_strlen(filename) + 1);
	}
	argv[0] = command_file;
	argv[1] = NULL;
	execve(command_file, argv, env);
	free(command_file);
}

// Interprete et lance le prompt
void	launch_line(t_global *global, char **env)
{
	if (!global)
		return ;
	while (global->token_list)
	{
		if (global->token_list->type == CMD)
			execute_command(global->token_list->token, env);
		global->token_list = global->token_list->next;
	}
}
