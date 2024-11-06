/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/11/04 16:30:05 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/04 16:43:23 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Malloc + initilise a 0 la structure global
void	calloc_global_struct(t_global **global_data)
{
	*global_data = ft_calloc(1, sizeof(t_global));
	if (!*global_data)
		return (perror("error, global struct calloc failed"));
	(*global_data)->line = NULL;
	(*global_data)->token_list = NULL;
}

// Initialise notre tableau de tableau de commandes (char ***)
char	***init_cmd_double_array(t_global *global)
{
	int		nbr_cmd;
	char	***cmd_arrays;

	if (!global)
		return (perror("error, struct not initialized"), NULL);
	nbr_cmd = count_cmd_token(global->token_list);
	cmd_arrays = ft_calloc((nbr_cmd + 1), sizeof(char **));
	if (!cmd_arrays)
	{
		free(cmd_arrays);
		return (perror("error, double array malloc failed"), NULL);
	}
	return (cmd_arrays);
}

char	**fill_arg_after_cmd(t_token *token_list)
{
	t_token	*current_token;
	char	**execve_args;
	int		nbr_arg;
	int		i;

	// int		y;
	i = -1;
	current_token = token_list;
	nbr_arg = nbr_arg_after_cmd(token_list);
	execve_args = malloc((nbr_arg + 1) * sizeof(char *));
	if (!execve_args)
	{
		free(execve_args);
		return (perror("error, malloc failed"), NULL);
	}
	current_token = current_token->next;
	while (++i < nbr_arg && current_token && current_token->type == ARG)
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
	/// TESTS A ENLEVER PLUS TARD ///////////////////////////////
	// y = 0;
	// while (execve_args[y])
	// {
	// 	printf("%s\n", execve_args[y]);
	// 	y++;
	// }
	////////////////////////////////////////////////////////////
	return (execve_args);
}

int	nbr_arg_after_cmd2(t_token *token_list)
{
	int		nbr_arg;
	t_token	*current_token;

	nbr_arg = 0;
	if (!token_list)
		return (perror("error, empty token list"), 0);
	current_token = token_list->next;
	while (current_token && current_token->type == ARG)
	{
		current_token = current_token->next;
		nbr_arg++;
	}
	return (nbr_arg);
}

void	init_env(t_env **env_to_add, char **env)
{
	int	i;

	i = 0;
	if (!env || !*env)
		return (perror("error, empty env list"));
	while (env[i])
	{
		env_add_node(env_to_add, env[i]);
		i++;
	}
}
