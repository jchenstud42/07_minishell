/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:16:11 by jchen             #+#    #+#             */
/*   Updated: 2024/11/04 11:59:48 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Permet d'obtenir le chemin absolu d'une commande
char	*get_command_path(const char *cmd, t_global *global)
{
	const char	*filename;
	char		*command_file;

	if (!cmd | !global)
		error_handler(EMPTY_LINE, global);
	filename = "/usr/bin/";
	command_file = malloc(ft_strlen(filename) + ft_strlen(cmd) + 1);
	if (!command_file)
		error_handler(MALLOC_FAILED, global);
	ft_strlcpy(command_file, filename, ft_strlen(filename) + 1);
	ft_strlcat(command_file, cmd, ft_strlen(filename) + ft_strlen(cmd) + 1);
	return (command_file);
}

// Compte le nombre d'ARG se trouvant apres une CMD
int	nbr_arg_after_cmd(t_token *token_list)
{
	int		nbr_arg;
	t_token	*current_token;

	nbr_arg = 1;
	if (!token_list)
		return (-1);
	current_token = token_list->next;
	while (current_token && current_token->type == ARG)
	{
		current_token = current_token->next;
		nbr_arg++;
	}
	return (nbr_arg);
}

// Remplie un tableau de string d'arguments qui seront utilises par execve()
// On en profite pour passer les noeuds possedant des ARG
char	**fill_execve_arg_array(t_global *global, t_token *token_list)
{
	t_token	*current_token;
	char	**execve_args;
	int		nbr_arg;
	int		i;

	i = -1;
	current_token = token_list;
	nbr_arg = nbr_arg_after_cmd(token_list);
	execve_args = malloc((nbr_arg + 1) * sizeof(char *));
	if (!execve_args)
	{
		free(execve_args);
		error_handler(MALLOC_FAILED, global);
	}
	while (++i < nbr_arg && current_token)
	{
		execve_args[i] = ft_strdup(current_token->token);
		if (!execve_args[i])
		{
			free_array(execve_args);
			error_handler(MALLOC_FAILED, global);
		}
		current_token = current_token->next;
	}
	execve_args[i] = NULL;
	return (execve_args);
}

// On utilise execve() pour lancer la commande/verifier si c'est une
// vraie commande
void	execute_command(char *cmd, char **env, t_global *global)
{
	char	*command_path;
	char	**execve_args;
	pid_t	pid;

	if (!cmd)
		return ;
	command_path = get_command_path(cmd, global);
	pid = fork();
	if (pid == -1)
	{
		free(command_path);
		error_handler(FORK_FAILED, global);
	}
	else if (pid == 0)
	{
		execve_args = fill_execve_arg_array(global, global->token_list);
		if (execve(command_path, execve_args, env) == -1)
			ft_printf("%s: command not found\n", cmd);
		free_array(execve_args);
		free(command_path);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, NULL, 0);
	free(command_path);
}
