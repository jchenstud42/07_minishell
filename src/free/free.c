/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/18 11:37:14 by jchen             #+#    #+#             */
/*   Updated: 2024/11/04 18:10:10 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Libere la memoire allouee a la token_list
void	free_token_list(t_token **token_list)
{
	t_token	*temp;
	t_token	*current;

	if (!token_list)
		return (perror("error, empty token list"));
	current = *token_list;
	while (current)
	{
		temp = current->next;
		free(current->token);
		free(current);
		current = temp;
	}
	*token_list = NULL;
}

// Libere la memoire allouee a un tableau de string
void	free_array(char **array)
{
	int	i;

	if (!array)
		return (perror("error, array"));
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

// Libere la memoire allouee a un tableau de tableau de string
void	free_double_array(char ***array_array)
{
	int	i;
	int	j;

	if (!array_array)
		return (perror("error, empty double array"));
	i = -1;
	while (array_array[++i])
	{
		j = -1;
		while (array_array[i][++j])
			free(array_array[i][j]);
		free(array_array[i]);
	}
	free(array_array);
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return (perror("error, empty env list"));
	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->env);
		free(tmp);
	}
}

// Libere toute la memoire allouee
void	free_all(t_global *global_data)
{
	if (global_data->token_list)
		free_token_list(&global_data->token_list);
	if (global_data->line)
		free(global_data->line);
	if (global_data->env_list)
		free_env_list(global_data->env_list);
	if (global_data)
		free(global_data);
}
