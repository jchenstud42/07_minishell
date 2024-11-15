/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:32:00 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/15 17:33:02 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// long long	atoi_exit(const char *arg, ????)
// {
// }

// Provoque l'arret du minishell avec un code de retour ($?) egal a n.
// Si n n'est pas précisé, le code de retour fourni est celui
// de la dernière commande exécutée.
// int	ft_exit(t_global *global, char **av)
// {
//		exit 0 bonjour :: bash: exit: too many arguments
// 		exit coucou :: exit: coucou: numeric argument required
// }

// https://github.com/iciamyplant/Minishell?tab=readme-ov-file#3-exit-et-
// https://github.com/jdecorte-be/42-minishell/blob/master/README.md#6-exit
// https://github.com/jdecorte-be/42-minishell/blob/master/README.md#5-exit_status
