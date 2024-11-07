/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:32:46 by jchen             #+#    #+#             */
/*   Updated: 2024/11/07 15:42:52 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Permet d'obtenir le chemin absolu d'une commande
// char *get_path(char *cmd, char **env)
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

// char	*get_command_path(const char *cmd, t_env *env)
// {
// 	const char	*filename;
// 	char		*command_file;

// 	if (!cmd | !env)
// 		return (perror("error, can't get cmd path"), NULL);
// 	filename = "/usr/bin/";
// 	command_file = malloc(ft_strlen(filename) + ft_strlen(cmd) + 1);
// 	if (!command_file)
// 		return (perror("error, malloc failed"), NULL);
// 	ft_strlcpy(command_file, filename, ft_strlen(filename) + 1);
// 	ft_strlcat(command_file, cmd, ft_strlen(filename) + ft_strlen(cmd) + 1);
// 	return (command_file);
// }

// Compte le nombre d'ARG se trouvant apres une CMD
int	nbr_arg_after_cmd(t_token *token_list)
{
	int		nbr_arg;
	t_token	*current_token;

	nbr_arg = 1;
	if (!token_list)
		return (perror("error, empty token list"), -1);
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
char	**fill_execve_arg_array(t_token *token_list)
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
		return (perror("error, malloc failed"), NULL);
	}
	while (++i < nbr_arg && current_token)
	{
		execve_args[i] = ft_strdup(current_token->token);
		if (!execve_args[i])
		{
			free_array(execve_args);
			return (perror("error, malloc failed"), NULL);
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
		return (perror("error, no command entered"));
	command_path = get_command_path(cmd);
	pid = fork();
	if (pid == -1)
	{
		free(command_path);
		return (perror("error, fork failed"));
	}
	else if (pid == 0)
	{
		execve_args = fill_execve_arg_array(global->token_list);
		if (execve(command_path, execve_args, env) == -1)
		{
			ft_putstr_fd(execve_args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		free_array(execve_args);
		free(command_path);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, NULL, 0);
	free(command_path);
}
