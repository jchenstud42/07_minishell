/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 13:32:40 by jchen             #+#    #+#             */
/*   Updated: 2024/12/14 13:33:07 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Libere toute la memoire allouee
void	free_all(t_global *global_data)
{
	int	e_value;

	e_value = global_data->exit_value;
	if (global_data->cmd_list)
		free_cmd_list(&global_data->cmd_list);
	if (global_data->token_list)
		free_token_list(&global_data->token_list);
	if (global_data->line)
		free(global_data->line);
	if (global_data->env_list)
		free_env_list(global_data->env_list);
	if (global_data->env_array)
		free_array(global_data->env_array);
	if (global_data->temp_str)
		free(global_data->temp_str);
	if (global_data)
		free(global_data);
	rl_clear_history();
	exit(e_value);
}

// Fonction de sortie.
void	exit_function(t_global *global, bool write_exit)
{
	if (write_exit == true && !pipe_inside_token_list(global))
		ft_printf("exit\n");
	free_all(global);
}
