/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:51:13 by jchen             #+#    #+#             */
/*   Updated: 2024/12/14 17:15:59 by jchen            ###   ########.fr       */
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

static void	exit_cmd_not_found(t_cmd *cmd_list, t_global *global)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_list->cmd, 2);
	ft_putstr_fd(" command not found\n", 2);
	global->exit_value = 127;
	exit_function(global, false);
}

static void	execute_child_process(t_cmd *cmd_list, char **env_array,
		t_global *global)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (global->cmd_list->outfile_cmd != -1)
		dup2(global->cmd_list->outfile_cmd, STDOUT_FILENO);
	if (global->cmd_list->infile_cmd != -1)
		dup2(global->cmd_list->infile_cmd, STDIN_FILENO);
	signal(SIGQUIT, SIG_DFL);
	if (!access(cmd_list->cmd, X_OK))
		execve(cmd_list->cmd, cmd_list->cmd_args, env_array);
	cmd_list->cmd_path = get_command_path(cmd_list->cmd);
	if (!cmd_list->cmd_path || ((execve(cmd_list->cmd_path, cmd_list->cmd_args,
					env_array) == -1) && !slash_in_cmd_token(cmd_list->cmd,
				true)))
		exit_cmd_not_found(cmd_list, global);
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		perror("Restauration stdin");
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		perror("Restauration stdout");
	close(saved_stdin);
	close(saved_stdout);
}

// static void	execute_child_process(t_cmd *cmd_list, char **env_array,
// 		t_global *global, t_token *token_list)
// {
// 	signal(SIGQUIT, SIG_DFL);
// 	if (!access(cmd_list->cmd, X_OK))
// 		execve(cmd_list->cmd, cmd_list->cmd_args, env_array);
// 	if (token_list->type == HEREDOC || token_list->type == APPEND
// 		|| token_list->type == INPUT || token_list->type == OUTPUT)
// 		return ;
// 	cmd_list->cmd_path = get_command_path(cmd_list->cmd);
// 	if (!cmd_list->cmd_path || ((execve(cmd_list->cmd_path, cmd_list->cmd_args,
// 					env_array) == -1) && !slash_in_cmd_token(cmd_list->cmd,
// 				true)))
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		ft_putstr_fd(cmd_list->cmd, 2);
// 		ft_putstr_fd(" command not found\n", 2);
// 		global->exit_value = 127;
// 		exit_function(global, false);
// 	}
// }

void	execute_command(t_global *global, t_cmd *cmd_list, t_env **env)
{
	pid_t	pid;

	if (global->env_array)
		free_array(global->env_array);
	global->env_array = get_env(*env);
	if (!check_valid_type(global->token_list, cmd_list)
		|| !check_env_path_exists(global, global->env_array, cmd_list))
		return ;
	pid = fork();
	if (pid == -1)
	{
		perror("error, fork failed");
		exit(1);
	}
	else if (pid == 0)
		execute_child_process(cmd_list, global->env_array, global);
	else
		catch_signals(global);
}
