/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:53:05 by jchen             #+#    #+#             */
/*   Updated: 2024/11/11 16:23:14 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	are_single_quotes_closed(int quote_count)
{
	return (quote_count % 2 == 0);
}

bool	are_double_quotes_closed(int quote_count)
{
	return (quote_count % 2 == 0);
}

// Verifie si les guillemets simples et doubles sont bien fermees
bool	are_all_quotes_closed(char *line)
{
	int	i;
	int	single_quote_count;
	int	double_quote_count;

	if (!line)
		return (false);
	i = -1;
	single_quote_count = 0;
	double_quote_count = 0;
	while (line[++i])
	{
		if (line[i] == '\'')
			single_quote_count++;
		else if (line[i] == '"')
			double_quote_count++;
	}
	return (are_double_quotes_closed(double_quote_count)
		&& are_single_quotes_closed(single_quote_count));
}

// si single quote et double quote(faux) :
// if (line[i] == '\'')
// single_quote(true);
// ignore tous les doubles quotes jusqua single.

// dou
