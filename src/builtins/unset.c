/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:44:15 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/25 10:26:16 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	unset_syntaxe(char *av)
{
	int	i;

	i = 0;
	if (av[0] != '_' || !ft_isalpha(av[0]))
		return (false);
	while (av[i])
	{
		if (av[i] == '_' || ft_isalnum(av[i]))
			return (false);
		i++;
	}
	return (true);
}

