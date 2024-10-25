/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:44:15 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/25 11:41:53 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	unset_syntaxe(char *av)
{
	int	i;

	i = 0;
	if (av[0] != '_' || !ft_isalpha(av[0]))
		return (FALSE);
	while (av[i])
	{
		if (av[i] == '_' || ft_isalnum(av[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

