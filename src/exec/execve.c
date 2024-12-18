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
/*   Created: 2024/12/14 16:51:13 by jchen             #+#    #+#             */
/*   Updated: 2024/12/16 16:53:21 by jchen            ###   ########.fr       */
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

static void	infile_outfile_handler(int *saved_stdin, int *saved_stdout,
		t_cmd *cmd, t_global *global)
{
	if (cmd->infile < -1 || cmd->outfile < -1)
		exit_function(global, false);
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (cmd->outfile > -1)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		close(cmd->outfile);
	}
	if (cmd->infile > -1)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
}

static void	execute_child_process(t_cmd *cmd_list, char **env_array,
		t_global *global)
{
	int	saved_stdin;
	int	saved_stdout;

	infile_outfile_handler(&saved_stdin, &saved_stdout, cmd_list, global);
	signal(SIGQUIT, SIG_DFL);
	if (!access(cmd_list->cmd, X_OK))
		execve(cmd_list->cmd, cmd_list->cmd_args, env_array);
	cmd_list->cmd_path = get_command_path(cmd_list->cmd);
	if (!cmd_list->cmd_path || ((execve(cmd_list->cmd_path, cmd_list->cmd_args,
					env_array) == -1) && !slash_in_cmd_token(cmd_list->cmd,
				true)))
		exit_cmd_not_found(cmd_list, global);
	if (dup2(saved_stdin, STDIN_FILENO) == -1 || dup2(saved_stdout,
			STDOUT_FILENO) == -1)
		perror("Restauration stdin");
	close(saved_stdin);
	close(saved_stdout);
}

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
