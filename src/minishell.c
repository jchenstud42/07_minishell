/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:55:30 by jchen             #+#    #+#             */
/*   Updated: 2024/12/13 13:40:59 by rbouquet         ###   ########.fr       */
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
			if (cmd->infile_cmd != -1)
			{
				close(cmd->infile_cmd);
				cmd->infile_cmd = -1;
			}
			if (cmd->outfile_cmd != -1)
			{
				close(cmd->outfile_cmd);
				cmd->outfile_cmd = -1;
			}
			cmd = cmd->next;
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_global	*global;

	calloc_global_struct(&global);
	minishell_initialization(global, ac, av, env);
	ft_printf("soucis avec echo $PWD qui ne se met pas a jour\n");
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
			launch_line(global, &global->env_list, global->token_list);
		cleaning_for_next_loop(global);
		printf("exit value : %d\n", global->exit_value);
	}
	free_all(global);
}
