/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:44:15 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/28 09:28:26 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	unset_syntaxe(char *line)
{
	int	i;

	i = 0;
	if (line[0] != '_' || !ft_isalpha(line[0]))
		return (0);
	while (line[i])
	{
		if (line[i] == '_' || ft_isalnum(line[i]))
			return (0);
		i++;
	}
	return (1);
}
