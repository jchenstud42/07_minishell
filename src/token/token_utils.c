/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/23 09:30:04 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/06 11:22:21 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


int	is_white_space(char c)
{
	return (((9 <= c) && (c <= 13)) || (c == 32));
}

// Passe les espaces au debut de la phrase s'il y en a
void	skip_beginning_white_space(int *end, char *line)
{
	int i;

	i = 0;
	if (!line)
		return (perror("error, empty line"));
	*end = 0;
	while (is_white_space(line[i]))
		i++;
	*end += i;
}

// Compte le nombre d'ARG se trouvant apres une CMD
int	nbr_arg_after_cmd(t_token *token_list)
{
	int nbr_arg;
	t_token *current_token;

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
