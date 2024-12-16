/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:55:30 by jchen             #+#    #+#             */
/*   Updated: 2024/12/16 17:41:17 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	minishell_initialization(t_global *global, int ac, char **av,
		char **env)
{
	(void)ac;
	(void)av;
	init_env_list(&global->env_list, env);
}

static void	cleaning_for_next_loop(t_global *global)
{
	t_cmd	*cmd;

	if (global->line)
		free(global->line);
	cmd = global->cmd_list;
	if (cmd)
	{
		while (cmd)
		{
			if (cmd->infile != -1)
				close(cmd->infile);
			if (cmd->outfile != -1)
				close(cmd->outfile);
			cmd->infile = -1;
			cmd->outfile = -1;
			cmd = cmd->next;
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_global	*global;

	calloc_global_struct(&global);
	minishell_initialization(global, ac, av, env);
	while (1)
	{
		init_signals(global);
		global->line = readline(GREEN "Minishell > " RESET);
		if (!global->line)
			exit_function(global, true);
		add_history(global->line);
		line_tokenization(&global, &global->line);
		init_cmd_list(&global->cmd_list, &global->token_list);
		if (!check_line(global, global->token_list))
			launch_line(global, &global->env_list);
		cleaning_for_next_loop(global);
		// printf("exit value : %d\n", global->exit_value);
	}
	free_all(global);
}
