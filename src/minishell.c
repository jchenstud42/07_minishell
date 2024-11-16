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
}

void	exit_function(t_global *global, int exit_value)
{
	free_all(global);
	ft_printf("exit\n");
	exit(exit_value);
}

int	main(int ac, char **av, char **env)
{
	t_global	*global;

	calloc_global_struct(&global);
	minishell_initialization(global, ac, av, env);
	while (1)
	{
		global->line = readline(GREEN "Minishell > " RESET);
		if (!global->line || ft_strcmp(global->line, "exit") == 0)
			exit_function(global, global->exit_value);
		add_history(global->line);
		line_tokenization(&global, global->line);
		init_cmd_list(&global->cmd_list, &global->token_list);
		if (!check_line(global, global->token_list))
			launch_line(global, env);
	}
	rl_clear_history();
	free_all(global);
	return (0);
}
