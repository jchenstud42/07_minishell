/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:55:55 by jchen             #+#    #+#             */
/*   Updated: 2024/12/02 12:19:32 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Compte le nombre de pipe
int	count_pipe(char *line)
{
	int	i;
	int	pipe_count;

	if (!line)
		return (-1);
	i = 0;
	pipe_count = 0;
	while (line[i])
	{
		if (line[i] == '|')
			pipe_count++;
		i++;
	}
	return (pipe_count);
}

// Compte le nombre de token CMD
int	count_cmd_token(t_token *token_list)
{
	t_token	*temp;
	int		cmd_count;

	temp = token_list;
	cmd_count = 0;
	while (temp)
	{
		if (temp->type == CMD)
			cmd_count++;
		temp = temp->next;
	}
	return (cmd_count);
}
