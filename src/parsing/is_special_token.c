/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_special_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:18:10 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/25 15:07:25 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Verifie si l'element est une redirection (INPUT, HEREDOC, TRUNC, APPEND)
int	is_redirection(char *str)
{
	if (!ft_strcmp(str, "<") || !ft_strcmp(str, "<<") || !ft_strcmp(str, ">")
		|| !ft_strcmp(str, ">>"))
		return (TRUE);
	return (FALSE);
}

// Verifie si l'element est une PIPE
int	is_pipe(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (TRUE);
	return (FALSE);
}

// TEST
// int	main(int ac, char **av)
// {
// 	if (ac == 2)
// 	{
// 		if (is_redirection(av[1]) || is_pipe(av[1]))
// 			ft_printf("ok\n");
// 		else
// 			ft_printf("error\n");
// 	}
// 	return (0);
// }
