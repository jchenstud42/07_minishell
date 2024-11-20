/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+
        +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+
        +#+        */
/*                                                +#+#+#+#+#+
        +#+           */
/*   Created: 2024/11/08 16:12:45 by jchen             #+#    #+#             */
/*   Updated: 2024/11/16 18:39:01 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Renvoie le dernier noeud de la structure de commandes.
t_cmd	*last_element_of_cmd_list(t_cmd *cmd_list) {
  if (!cmd_list)
    return (NULL);
  while (cmd_list->next)
    cmd_list = cmd_list->next;
  return (cmd_list);
}

// Ajoute un noeud a la fin de notre structure de commandes.
void	append_node_to_cmd_list(t_cmd **cmd) {
  t_cmd *cmd_to_append;
  t_cmd *last_node;

  cmd_to_append = ft_calloc(1, sizeof(t_cmd));
  if (!cmd_to_append)
    return (perror("error, cmd list malloc failed"));
  cmd_to_append->infile_cmd = -1;
  cmd_to_append->outfile_cmd = -1;
  if (*cmd == NULL) {
    *cmd = cmd_to_append;
    cmd_to_append->prev = NULL;
  } else {
    last_node = last_element_of_cmd_list(*cmd);
    last_node->next = cmd_to_append;
    cmd_to_append->prev = last_node;
  }
}

// Remplie le <cmd_args> de notre structure de commande.
char	**fill_cmd_args(t_token *token_list) {
  t_token *current_token;
  char **cmd_args;
  int nbr_arg;
  int i;

  i = -1;
  current_token = token_list;
  nbr_arg = nbr_arg_after_cmd(token_list);
  cmd_args = malloc((nbr_arg + 1) * sizeof(char *));
  if (!cmd_args) {
    free(cmd_args);
    return (perror("error, malloc failed"), NULL);
  }
  while (++i < nbr_arg && current_token) {
    cmd_args[i] = ft_strdup(current_token->token);
    if (!cmd_args[i]) {
      free_array(cmd_args);
      return (perror("error, malloc failed"), NULL);
    }
    current_token = current_token->next;
  }
  cmd_args[i] = NULL;
  /// TESTS A ENLEVER PLUS TARD ///////////////////////////////
  // y = 0;
  // while (cmd_args[y])
  // {
  // 	printf("cmd_arg : %s\n", cmd_args[y]);
  // 	y++;
  // }
  ////////////////////////////////////////////////////////////
  return (cmd_args);
}

// Ajoute la CMD ainsi que les ARG qui suivent au noeud
// de la structure de commandes.
void	fill_cmd_node(t_cmd **cmd, t_token *current_token) {
  t_cmd *last_cmd;

  last_cmd = last_element_of_cmd_list(*cmd);
  if (last_cmd->cmd == NULL) {
    last_cmd->cmd = ft_strdup(current_token->token);
    last_cmd->cmd_args = fill_cmd_args(current_token);
  } else {
    append_node_to_cmd_list(cmd);
    last_cmd = last_element_of_cmd_list(*cmd);
    last_cmd->cmd = ft_strdup(current_token->token);
    last_cmd->cmd_args = fill_cmd_args(current_token);
  }
}

// Initialise notre structure de commandes.
void	init_cmd_list(t_cmd **cmd, t_token **token) {
  t_token *current_token;

  if (cmd && *cmd)
    free_cmd_list(cmd);
  current_token = *token;
  if (!current_token)
    return ;
  append_node_to_cmd_list(cmd);
  while (current_token) {
    if (current_token->type == CMD)
      fill_cmd_node(cmd, current_token);
    else if (current_token->type == PIPE)
      append_node_to_cmd_list(cmd);
    current_token = current_token->next;
  }
}

// void	init_cmd_list(t_cmd **cmd, t_token **token)
// {
// 	t_token	*current_token;

// 	// t_cmd	*start_cmd;
// 	// t_cmd	*last_cmd_in_list;
// 	if (cmd)
// 		free_cmd_list(cmd);
// 	current_token = *token;
// 	if (!current_token)
// 		return ;
// 	append_node_to_cmd_list(cmd);
// 	// last_cmd_in_list = last_element_of_cmd_list(*cmd);
// 	while (current_token)
// 	{
// 		if (current_token->type == CMD)
// 			fill_cmd_node(cmd, current_token);
// 		// else if (current_token->type == INPUT
// ||
// current_token->type ==
// TRUNC
// 		// 	|| current_token->type == HEREDOC
// || current_token->type == APPEND)
// 		// 	handle_input_output(last_cmd_in_list, current_token,
// global);
// 		else if (current_token->type == PIPE)
// 			append_node_to_cmd_list(cmd);
// 		current_token = current_token->next;
// 	}
// 	///// TEST PRINT ///////////////////////////////////////////
// 	// start_cmd = *cmd;
// 	// while (start_cmd)
// 	// {
// 	// 	ft_printf("[cmd : %s]\n", start_cmd->cmd);
// 	// 	start_cmd = start_cmd->next;
// 	// }
// 	////////////////////////////////////////////////////////////
// }
