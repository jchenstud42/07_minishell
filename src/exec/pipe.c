/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:20:49 by jchen             #+#    #+#             */
/*   Updated: 2024/11/04 12:08:36 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Simule les pipes
void	pipeline(char ***cmd, char **env, t_global *global)
{
	int		fds[2];
	int		backup_fd;
	char	*cmd_path;
	pid_t	pid;

	backup_fd = 0;
	while (*cmd != NULL)
	{
		pipe(fds);
		if ((pid = fork()) == -1)
			error_handler(FORK_FAILED, global);
		else if (pid == 0)
		{
			dup2(backup_fd, 0);
			if (*(cmd + 1) != NULL)
			{
				dup2(fds[1], 1);
			}
			close(fds[0]);
			cmd_path = get_command_path((*cmd)[0], global);
			if (execve(cmd_path, *cmd, env) == -1)
				ft_printf("%s: command not found\n", cmd);
			free(cmd_path);
			exit(1);
		}
		else
		{
			wait(NULL);
			close(fds[1]);
			backup_fd = fds[0];
			cmd++;
		}
	}
}

// Remplie un double tableau de string d'arguments
// qui seront utilises par execve()
char	***fill_cmd_double_array(t_token *token_list, char ***cmd_arrays,
		t_global *global)
{
	t_token	*current_token;
	int		i;

	if (!token_list || !cmd_arrays)
		return (NULL);
	i = -1;
	current_token = token_list;
	while (current_token)
	{
		if (current_token->type == CMD)
			cmd_arrays[++i] = fill_execve_arg_array(global, current_token);
		current_token = current_token->next;
	}
	return (cmd_arrays);
}

// Prepare et launch le code comme si on utilisait les pipes
void	execute_pipe(char *line, char **env, t_global *global)
{
	char	***cmd_arrays;

	// int		i;
	// int		j;
	if (!line || !env || !global)
		error_handler(STRUCT_INIT_FAILED, global);
	cmd_arrays = init_cmd_double_array(global);
	fill_cmd_double_array(global->token_list, cmd_arrays, global);
	//// TEST POUR PRINT - A ENLEVER PLUS TARD ///////////////////////
	// i = -1;
	// while (cmd_arrays[++i])
	// {
	// 	j = -1;
	// 	while (cmd_arrays[i][++j])
	// 		printf("[%d - %d] : %s\n", i, j, cmd_arrays[i][j]);
	// 	printf("\n");
	// }
	//// FIN TEST POUR PRINT //////////////////////////////////////////
	pipeline(cmd_arrays, env, global);
	free_double_array(cmd_arrays);
}
