/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:27:56 by jchen             #+#    #+#             */
/*   Updated: 2024/10/23 14:49:41 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_global	*global;
	char		*line;
	int			i;

	i = 0;
	(void)ac;
	(void)av;
	(void)env;
	calloc_global_struct(&global);
	while (1)
	{
		line = readline("minishell >");
		if (!line)
			free_all(global);
		add_history(line);
	}
	rl_clear_history();
	free_all(global);
	return (0);
}
