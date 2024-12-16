/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:56:51 by jchen             #+#    #+#             */
/*   Updated: 2024/12/16 14:44:00 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Ajoute un noeud a la fin de notre structure de commandes.
void	append_node_to_cmd_list(t_cmd **cmd)
{
	t_cmd	*cmd_to_append;
	t_cmd	*last_node;

	cmd_to_append = ft_calloc(1, sizeof(t_cmd));
	if (!cmd_to_append)
		return (perror("error, cmd list malloc failed"));
	cmd_to_append->infile_cmd = -1;
	cmd_to_append->outfile_cmd = -1;
	cmd_to_append->filename = NULL;
	if (*cmd == NULL)
	{
		*cmd = cmd_to_append;
		cmd_to_append->prev = NULL;
	}
	else
	{
		last_node = last_element_of_cmd_list(*cmd);
		last_node->next = cmd_to_append;
		cmd_to_append->prev = last_node;
	}
}

// Remplie le <cmd_args> de notre structure de commande.
char	**fill_cmd_args(t_token *token_list)
{
	t_token	*current_token;
	char	**cmd_args;
	int		nbr_arg;
	int		i;

	i = -1;
	current_token = token_list;
	nbr_arg = nbr_arg_after_cmd(token_list);
	cmd_args = malloc((nbr_arg + 1) * sizeof(char *));
	if (!cmd_args)
		return (free(cmd_args), perror("error, malloc failed"), NULL);
	while (++i < nbr_arg && current_token)
	{
		cmd_args[i] = ft_strdup(current_token->token);
		if (!cmd_args[i])
		{
			free_array(cmd_args);
			return (perror("error, malloc failed"), NULL);
		}
		current_token = current_token->next;
	}
	cmd_args[i] = NULL;
	return (cmd_args);
}

// Ajoute la CMD ainsi que les ARG qui suivent au noeud
// de la structure de commandes.
void	fill_cmd_node(t_cmd **cmd, t_token *current_token)
{
	t_cmd	*last_cmd;

	last_cmd = last_element_of_cmd_list(*cmd);
	if (last_cmd->cmd == NULL)
	{
		last_cmd->cmd = ft_strdup(current_token->token);
		last_cmd->cmd_args = fill_cmd_args(current_token);
	}
	else
	{
		append_node_to_cmd_list(cmd);
		last_cmd = last_element_of_cmd_list(*cmd);
		last_cmd->cmd = ft_strdup(current_token->token);
		last_cmd->cmd_args = fill_cmd_args(current_token);
	}
}

static void	handle_input_output(t_cmd **cmd, t_token *current_token)
{
	t_cmd	*last_cmd;

	last_cmd = last_element_of_cmd_list(*cmd);
	if (current_token->type == INPUT)
		last_cmd->infile_cmd = INPUT;
	else if (current_token->type == HEREDOC)
		last_cmd->infile_cmd = HEREDOC;
	else if (current_token->type == APPEND)
		last_cmd->outfile_cmd = APPEND;
	else if (current_token->type == OUTPUT)
		last_cmd->outfile_cmd = OUTPUT;
	if (current_token->next)
		last_cmd->filename = ft_strdup(current_token->next->token);
}

// Initialise notre structure de commandes.
void	init_cmd_list(t_cmd **cmd, t_token **token)
{
	t_token	*current_token;

	if (cmd && *cmd)
		free_cmd_list(cmd);
	current_token = *token;
	if (!current_token)
		return ;
	append_node_to_cmd_list(cmd);
	while (current_token)
	{
		if (current_token->type == CMD)
			fill_cmd_node(cmd, current_token);
		else if (1 <= current_token->type && current_token->type <= 4)
			handle_input_output(cmd, current_token);
		else if (current_token->type == PIPE)
			append_node_to_cmd_list(cmd);
		current_token = current_token->next;
	}
	///// TEST PRINT ///////////////////////////////////////////
	// t_cmd	*start_cmd;
	// start_cmd = *cmd;
	// while (start_cmd)
	// {
	// 	printf("%s [in %d] [out %d] ", start_cmd->cmd, start_cmd->infile_cmd,
	// 			start_cmd->outfile_cmd);
	// 	printf("[file : %s\n]", start_cmd->filename);
	// 	start_cmd = start_cmd->next;
	// }
	////////////////////////////////////////////////////////////
}
