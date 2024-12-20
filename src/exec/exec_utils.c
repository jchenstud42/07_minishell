/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:41:01 by jchen             #+#    #+#             */
/*   Updated: 2024/12/18 09:16:32 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// WIFEXITED : retoune vrai si le child s'est terminé normalement
// WIFEXITSATUS : code de sortie du processus
// WIFSIGNALED : retourne vrai si un signal a causé la terminaison
// WTERMSIG :renvoie le numero du signal qui a cause la terminaison
void	status_child(t_global *global, pid_t pid)
{
	int	signal;

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

void	catch_signals(t_global *global)
{
	int	status;

	signal(SIGINT, handle_nl);
	signal(SIGQUIT, handle_nl);
	while (wait(&status) > 0)
		;
	status_child(global, status);
	signal(SIGINT, SIG_DFL);
}

bool	check_env_path_exists(t_global *global, char **env_array,
		t_cmd *cmd_list)
{
	int		i;
	bool	path_found;

	i = 0;
	path_found = false;
	while (env_array[i] != NULL)
	{
		if (ft_strncmp(env_array[i], "PATH=", 5) == 0)
		{
			path_found = true;
			break ;
		}
		i++;
	}
	if (!path_found)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_list->cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		global->exit_value = 127;
		return (false);
	}
	return (true);
}

bool	check_valid_type(t_token *token_list, t_cmd *cmd_list)
{
	t_token	*tmp;
	bool	valid_type_found;

	valid_type_found = false;
	tmp = token_list;
	while (tmp)
	{
		if (tmp->type == HEREDOC || tmp->type == APPEND || tmp->type == INPUT
			|| tmp->type == OUTPUT)
		{
			valid_type_found = true;
			break ;
		}
		tmp = tmp->next;
	}
	if (!valid_type_found)
	{
		if (!cmd_list->cmd)
			return (ft_putstr_fd("error, no command entered\n", 2), false);
	}
	return (true);
}

// Renvoie le dernier noeud de la structure de commandes.
t_cmd	*last_element_of_cmd_list(t_cmd *cmd_list)
{
	if (!cmd_list)
		return (NULL);
	while (cmd_list->next)
		cmd_list = cmd_list->next;
	return (cmd_list);
}
