/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:44:15 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/15 15:26:03 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	unset_syntaxe(char *line)
{
	int	i;

	i = 0;
	if (line[0] != '_' || !ft_isalpha(line[0]))
		return (1);
	while (line[i])
	{
		if (line[i] != '_' && !ft_isalnum(line[i]))
			return (1);
		i++;
	}
	return (0);
}
