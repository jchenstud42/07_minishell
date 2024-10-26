/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:20:57 by jchen             #+#    #+#             */
/*   Updated: 2024/10/26 17:29:01 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// // Replique la commande env (vite fait)
// int	getenv_example(void)
// {
// 	const char	*home;

// 	home = getenv("HOME");
// 	if (!home)
// 		return (1);
// 	printf("HOME=%s\n", home);
// 	return (0);
// }

// // Replique MIEUX la commande env, en prenant en parametre env
// int	getenv_false_example(char **env)
// {
// 	char	**print_env;

// 	print_env = env;
// 	while (*print_env)
// 	{
// 		ft_printf("%s\n", *print_env);
// 		print_env++;
// 	}
// 	return (0);
// }
