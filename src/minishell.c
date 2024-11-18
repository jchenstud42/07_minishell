/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:14:55 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/18 13:14:57 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	minishell_initialization(t_global *global, int ac, char **av,
		char **env)
{
	(void)ac;
	(void)av;
	init_signals();
	init_env_list(&global->env_list, env);
}

int	main(int ac, char **av, char **env)
{
	t_global	*global;

	calloc_global_struct(&global);
	minishell_initialization(global, ac, av, env);
	while (1)
	{
		global->line = readline(GREEN "Minishell > " RESET);
		if (!global->line)
			exit_function(global, true);
		add_history(global->line);
		line_tokenization(&global, global->line);
		init_cmd_list(&global->cmd_list, &global->token_list);
		if (!check_line(global, global->token_list))
			launch_line(global, &global->env_list);
	}
	free_all(global);
}
