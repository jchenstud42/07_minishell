/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:09:49 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/26 12:18:49 by rbouquet         ###   ########.fr       */
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

char	*get_command_path(const char *cmd, t_global *global)
{
	const char	*filename;
	char		*command_file;

	filename = "/usr/bin/";
	command_file = malloc(ft_strlen(filename) + ft_strlen(cmd) + 1);
	if (!command_file)
		error_handler(MALLOC_FAILED, global);
	ft_strlcpy(command_file, filename, ft_strlen(filename) + 1);
	ft_strlcat(command_file, cmd, ft_strlen(filename) + ft_strlen(cmd) + 1);
	if (access(command_file, X_OK) != 0)
	{
		free(command_file);
		error_handler(COMMAND_NOT_FOUND, global);
	}
	return (command_file);
}

void	execute_command(char *cmd, char **env, t_global *global)
{
	char		*command_file;
	char		*argv[2];
	pid_t		pid;

	if (!cmd)
		return ;
	command_file = get_command_path(cmd, global);
	pid = fork();
	if (pid == -1)
	{
		free(command_file);
		error_handler(FORK_FAILED, global);
	}
	else if (pid == 0)
	{
		argv[0] = command_file;
		argv[1] = NULL;
		if (execve(command_file, argv, env) == -1)
			error_handler(EXECVE_FAILED, global);
		free(command_file);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, NULL, 0);
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
			execute_command(global->token_list->token, env, global);
		global->token_list = global->token_list->next;
	}
}
