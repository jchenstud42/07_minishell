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

// Permet d'obtenir le chemin absolu d'une commande
char	*get_command_path(const char *cmd)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;

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

void	execute_command(t_cmd *cmd_list, char **env)
{
	char	*command_path;
	pid_t	pid;

	if (!cmd_list->cmd)
		return (perror("error, no command entered"));
	command_path = get_command_path(cmd_list->cmd);
	pid = fork();
	if (pid == -1)
	{
		free(command_path);
		return (perror("error, fork failed"));
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (!access(cmd_list->cmd, X_OK))
			execve(cmd_list->cmd, cmd_list->cmd_args, env);
		else if (execve(command_path, cmd_list->cmd_args, env) == -1)
		{
			ft_putstr_fd(cmd_list->cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		free(command_path);
		exit(EXIT_FAILURE);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, NULL, 0);
		signal(SIGINT, sig_c);
	}
	free(command_path);
}

// void	execute_command(t_cmd *cmd_list, char **env)
// {
// 	char *command_path;
// 	pid_t pid;

// 	if (!cmd_list->cmd)
// 		return (perror("error, no command entered"));
// 	command_path = get_command_path(cmd_list->cmd);
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		free(command_path);
// 		return (perror("error, fork failed"));
// 	}
// 	else if (pid == 0)
// 	{
// 		if (execve(command_path, cmd_list->cmd_args, env) == -1)
// 		{
// 			ft_putstr_fd(cmd_list->cmd, 2);
// 			ft_putstr_fd(": command not found\n", 2);
// 		}
// 		free(command_path);
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 		waitpid(pid, NULL, 0);
// 	free(command_path);
// }
