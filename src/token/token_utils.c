/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:38:46 by jchen             #+#    #+#             */
/*   Updated: 2024/12/09 16:41:08 by jchen            ###   ########.fr       */
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
	int	i;

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

bool	quotes_are_closed(char *line)
{
	int		i;
	bool	single_quotes;
	bool	double_quotes;

	i = 0;
	single_quotes = false;
	double_quotes = false;
	while (line && line[i])
	{
		if (line[i] == '\'' && !double_quotes)
			single_quotes = !single_quotes;
		else if (line[i] == '"' && !single_quotes)
			double_quotes = !double_quotes;
		i++;
	}
	if (single_quotes || double_quotes)
	{
		ft_putstr_fd("minishell: error, ", 2);
		ft_putstr_fd("quotes are not closed\n", 2);
		return (false);
	}
	return (true);
}
