/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/11/06 12:32:46 by jchen             #+#    #+#             */
/*   Updated: 2024/11/07 15:42:52 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


// WIFEXITED : retoune vrai si le child s'est terminé normalement
// WIFEXITSATUS : code de sortie du processus
// WIFSIGNALED : retourne vrai si un signal a causé la terminaison
// WTERMSIG :renvoie le numero du signal qui a cause la terminaison
void	status_child(t_global *global, pid_t pid)
{
	int signal;

	signal = WTERMSIG(pid);
	if (WIFEXITED(pid))
		global->exit_value = WEXITSTATUS(pid);
	else if (WIFSIGNALED(pid))
	{
		if (signal == SIGPIPE)
			global->exit_value = 0;
		else
		{
			global->exit_value = WTERMSIG(pid);
			if (global->exit_value != 131)
				global->exit_value = WTERMSIG(pid) + 128;
		}
	}
}

// Permet d'obtenir le chemin absolu d'une commande
char	*get_command_path(const char *cmd)
{
	int i;
	char *exec;
	char **allpath;
	char *path_part;

	allpath = ft_split(getenv("PATH"), ':');
	if (!allpath)
		return (perror("error, path variable not set"), NULL);
	i = -1;
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, cmd);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free_array(allpath);
			return (exec);
		}
		free(exec);
	}
	free_array(allpath);
	return (NULL);
}

void	execute_command(t_global *global, t_cmd *cmd_list, t_env **env)
{
	pid_t pid;
	char **env_cpy;
	int status;

	env_cpy = get_env(*env);
	if (!cmd_list->cmd)
		return (perror("error, no command entered"));
	pid = fork();
	if (pid == -1)
	{
		perror("error, fork failed");
		exit(1);
	}
	else if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (!access(cmd_list->cmd, X_OK))
			execve(cmd_list->cmd, cmd_list->cmd_args, env_cpy);
		cmd_list->cmd_path = get_command_path(cmd_list->cmd);
		if ((execve(cmd_list->cmd_path, cmd_list->cmd_args, env_cpy) == -1)
			&& !slash_in_cmd_token(cmd_list->cmd, true))
		{
			ft_putstr_fd(cmd_list->cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
			global->exit_value = 127;
			free_array(env_cpy);
			exit_function(global, false);
		}
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_nl);
		signal(SIGQUIT, handle_nl);
		while (wait(&status) > 0)
			;
		status_child(global, status);
		signal(SIGINT, SIG_DFL);
	}
}
