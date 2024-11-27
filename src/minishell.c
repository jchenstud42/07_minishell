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


static void	minishell_initialization(t_global *global, int ac, char **av,
		char **env)
{
	(void)ac;
	(void)av;
	init_env_list(&global->env_list, env);
}

int	main(int ac, char **av, char **env)
{
	t_global *global;

	calloc_global_struct(&global);
	minishell_initialization(global, ac, av, env);
	while (1)
	{
		init_signals(global);
		global->line = readline(GREEN "Minishell > " RESET);
		if (!global->line)
			exit_function(global, true);
		add_history(global->line);
		line_tokenization(&global, global->line);
		init_cmd_list(&global->cmd_list, &global->token_list);
		if (!check_line(global, global->token_list))
			launch_line(global, &global->env_list, global->token_list);
		printf("exit value : %d\n", global->exit_value);
	}
	free_all(global);
}

//// NOTES A NOUS MEME : /////////////////////////////////////////////////////
//
// - [env] "unset PATH" puis "ls" marche, alors que normalement non;
// - [heredoc] Ne fonctionne pas avec un arg avant ("x << FIN");
// - [exit_value] si seulement Ctrl+C, l'exit value ne se met pas a jour
// - [parsing : quotes] "echo > <" ne fonctionne pas,
// 				car > et < sont considérés comme des redirections;
