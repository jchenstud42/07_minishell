/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/18 11:27:56 by jchen             #+#    #+#             */
/*   Updated: 2024/11/04 17:51:59 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


void	minishell_initialization(t_global *global, int ac, char **av,
		char **env)
{
	(void)ac;
	(void)av;

	init_signals();
	init_env_list(&global->env_list, env);
	init_env(global->env_list);
}

int	main(int ac, char **av, char **env)
{
	t_global *global;

	while (1)
	{
		calloc_global_struct(&global);
		minishell_initialization(global, ac, av, env);
		global->line = readline(GREEN "Minishell > " RESET);
		if (!global->line || ft_strcmp(global->line, "exit") == 0)
		{
			ft_printf("exit\n");
			break ;
		}
		add_history(global->line);
		line_tokenization(&global, global->line);
		init_cmd_list(&global->cmd_list, &global->token_list);
		if (!check_line(global, global->token_list))
		{
			launch_line(global, env);
		}
	}
	rl_clear_history();
	free_all(global);
	return (0);
}
