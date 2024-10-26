/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:27:56 by jchen             #+#    #+#             */
/*   Updated: 2024/10/26 09:51:07 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_global	*global;
	char		*line;

	(void)ac;
	(void)av;
	(void)env;
	calloc_global_struct(&global);
	while (1)
	{
		line = readline("\033[1;032mMinishell> \033[m");
		// "exit" + Ctrl D
		if (!line || ft_strcmp(line, "exit") == 0)
		{
			ft_printf("exit\n");
			free(line);
			break ;
		}
		line_tokenization(&global, line);
		launch_line(global, env);
		add_history(line);
	}
	rl_clear_history();
	free_all(global);
	return (0);
}
