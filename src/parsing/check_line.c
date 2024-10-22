/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:00:20 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/22 14:08:43 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

"../../inc/minishell.h"

	int
	check_pipe(t_global *global)
{
	int	pipe_count;

	pipe_count = 0;
	while (global->line)
	{
		if (global->line == '|')
			pipe_count++;
		global->line++;
	}
	return (pipe_count);
}
