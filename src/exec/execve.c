/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:16:11 by jchen             #+#    #+#             */
/*   Updated: 2024/10/28 15:16:21 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Permet d'obtenir le chemin absolu d'une commande
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
	return (command_file);
}

// Compte le nombre d'ARG se trouvant apres une CMD
int	nbr_arg_after_cmd(t_global *global)
{
	int		nbr_arg;
	t_token	*current_token;

	nbr_arg = 1;
	if (!global)
		error_handler(STRUCT_NOT_INITIALIZED, global);
	current_token = global->token_list->next;
	while (current_token && current_token->type == ARG)
	{
		current_token = current_token->next;
		nbr_arg++;
	}
	return (nbr_arg);
}

// Remplie un tableau de string d'arguments qui vont etre utilises par execve()
// On en profite pour passer les noeuds possedant des ARG
char	**fill_execve_arg_array(t_global *global)
{
	char	**execve_args;
	int		nbr_arg;
	int		i;

	i = -1;
	nbr_arg = nbr_arg_after_cmd(global);
	execve_args = malloc((nbr_arg + 1) * sizeof(char *));
	if (!execve_args)
	{
		free(execve_args);
		error_handler(MALLOC_FAILED, global);
	}
	while (nbr_arg > ++i)
	{
		execve_args[i] = ft_strdup(global->token_list->token);
		if (!execve_args[i])
		{
			free_array(execve_args);
			error_handler(MALLOC_FAILED, global);
		}
		global->token_list = global->token_list->next;
	}
	execve_args[i] = NULL;
	return (execve_args);
}

// On utilise execve() pour lancer la commande/verifier si c'est une
// vraie commande
void	execute_command(char *cmd, char **env, t_global *global)
{
	char	*command_file;
	char	**execve_args;
	pid_t	pid;

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
		execve_args = fill_execve_arg_array(global);
		if (execve(command_file, execve_args, env) == -1)
			ft_printf("%s: command not found\n", cmd);
		free_array(execve_args);
		free(command_file);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, NULL, 0);
	free(command_file);
}
