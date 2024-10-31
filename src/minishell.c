/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:27:56 by jchen             #+#    #+#             */
/*   Updated: 2024/10/31 10:29:24 by rbouquet         ###   ########.fr       */
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
	while (1)
	{
		calloc_global_struct(&global);
		init_signals();
		line = readline("\033[1;032mMinishell > \033[m");
		// "exit" + Ctrl D
		if (!line || ft_strcmp(line, "exit") == 0)
		{
			ft_printf("exit\n");
			free(line);
			break ;
		}
		add_history(line);
		if (!check_line(global, global->token_list))
		{
			line_tokenization(&global, line);
			launch_line(global, env);
		}
	}
	rl_clear_history();
	free_all(global);
	return (0);
}
