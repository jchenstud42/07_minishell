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

static void	execute_child_process(t_cmd *cmd_list, char **env_array,
		t_global *global)
{
	signal(SIGQUIT, SIG_DFL);
	if (!access(cmd_list->cmd, X_OK))
		execve(cmd_list->cmd, cmd_list->cmd_args, env_array);
	cmd_list->cmd_path = get_command_path(cmd_list->cmd);
	if (!cmd_list->cmd_path || ((execve(cmd_list->cmd_path, cmd_list->cmd_args,
					env_array) == -1) && !slash_in_cmd_token(cmd_list->cmd,
				true)))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_list->cmd, 2);
		ft_putstr_fd(" command not found\n", 2);
		global->exit_value = 127;
		exit_function(global, false);
	}
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

// void	execute_command(t_global *global, t_cmd *cmd_list, t_env **env,
// 		t_token *token_list)
// {
// 	pid_t	pid;
// 	t_token	*tmp;
// 	char	**env_cpy;
// 	int		valid_type_found;
// 	int		path_found;
// 	int		i;

// 	valid_type_found = 0;
// 	tmp = token_list;
// 	env_cpy = get_env(*env);
// 	while (tmp)
// 	{
// 		if (tmp->type == HEREDOC || tmp->type == TRUNC || tmp->type == INPUT
// 			|| tmp->type == APPEND)
// 		{
// 			valid_type_found = 1;
// 			break ;
// 		}
// 		tmp = tmp->next;
// 	}
// 	if (!valid_type_found)
// 	{
// 		if (!cmd_list->cmd)
// 			return (ft_putstr_fd("error, no command entered\n", 2));
// 	}
// 	path_found = 1;
// 	i = 0;
// 	while (env_cpy[i] != NULL)
// 	{
// 		if (ft_strncmp(env_cpy[i], "PATH=", 5) == 0)
// 		{
// 			path_found = 0;
// 			break ;
// 		}
// 		i++;
// 	}
// 	if (path_found)
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		ft_putstr_fd(cmd_list->cmd, 2);
// 		ft_putstr_fd(": No such file or directory\n", 2);
// 		free_array(env_cpy);
// 		return ;
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("error, fork failed");
// 		exit(1);
// 	}
// 	else if (pid == 0)
// 	{
// 		signal(SIGQUIT, SIG_DFL);
// 		if (!access(cmd_list->cmd, X_OK))
// 			execve(cmd_list->cmd, cmd_list->cmd_args, env_cpy);
// 		cmd_list->cmd_path = get_command_path(cmd_list->cmd);
// 		if (!cmd_list->cmd_path || ((execve(cmd_list->cmd_path,
// 						cmd_list->cmd_args, env_cpy) == -1)
// 				&& !slash_in_cmd_token(cmd_list->cmd, true)))
// 		{
// 			ft_putstr_fd("minishell: ", 2);
// 			ft_putstr_fd(cmd_list->cmd, 2);
// 			ft_putstr_fd(" command not found\n", 2);
// 			global->exit_value = 127;
// 			free_array(env_cpy);
// 			exit_function(global, false);
// 		}
// 	}
// 	else
// 		catch_signals(global);
// }
