/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:27:56 by jchen             #+#    #+#             */
/*   Updated: 2024/10/25 14:01:21 by jchen            ###   ########.fr       */
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
		if (!line)
			error_handler(EMPTY_LINE, global);
		line_tokenization(&global, line);
		add_history(line);
	}
	rl_clear_history();
	free_all(global);
	return (0);
}
