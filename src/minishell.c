/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:27:56 by jchen             #+#    #+#             */
/*   Updated: 2024/11/04 17:51:59 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// int	main(int ac, char **av, char **env)
// {
// 	t_global	*global;
// 	char		*line;

// 	(void)ac;
// 	(void)av;
// 	while (1)
// 	{
// 		calloc_global_struct(&global);
// 		init_signals();
// 		line = readline("\033[1;032mMinishell > \033[m");
// 		// "exit" + Ctrl D
// 		if (!line || ft_strcmp(line, "exit") == 0)
// 		{
// 			ft_printf("exit\n");
// 			free(line);
// 			break ;
// 		}
// 		add_history(line);
// 		line_tokenization(&global, line);
// 		if (!check_line(global, global->token_list))
// 		{
// 			launch_line(global, env);
// 		}
// 	}
// 	rl_clear_history();
// 	free_all(global);
// 	return (0);
// }

int	main(int ac, char **av, char **env)
{
	t_global	*global;
	char		*line;

	(void)env;
	(void)ac;
	(void)av;
	while (1)
	{
		calloc_global_struct(&global);
		init_signals();
		init_env(&global->env_list, env);
		line = readline("\033[1;032mMinishell > \033[m");
		// "exit" + Ctrl D
		if (!line || ft_strcmp(line, "exit") == 0)
		{
			ft_printf("exit\n");
			free(line);
			break ;
		}
		add_history(line);
		line_tokenization(&global, line);
		if (!check_line(global, global->token_list))
		{
			launch_line(global, env);
		}
	}
	rl_clear_history();
	free_all(global);
	// NOTE A MOI MEME POUR ME RAPPELER QUOI FAIRE LA PROCHAINE FOIS
	ft_printf("NOTE A ROMAIN (DE ROMAIN): ");
	ft_printf("FAIS EN SORTE D'UTILISER LES BUILTINS, ENV ET PWD C'EST BON");
	return (0);
}
