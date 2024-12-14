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

// Libere la memoire allouee a un tableau de string
void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}

// Libere la memoire allouee a la token_list
void	free_token_list(t_token **token_list)
{
	t_token	*temp;
	t_token	*current;

	if (!token_list)
		return ;
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

// Libere la memoire allouee a la structure t_cmd
void	free_cmd_list(t_cmd **cmd_list)
{
	t_cmd	*temp;
	t_cmd	*current;

	if (!cmd_list)
		return ;
	current = *cmd_list;
	while (current)
	{
		temp = current->next;
		if (current->cmd)
			free(current->cmd);
		if (current->cmd_path)
			free(current->cmd_path);
		if (current->cmd_args)
			free_array(current->cmd_args);
		if (current->filename)
			free(current->filename);
		free(current);
		current = temp;
	}
	*cmd_list = NULL;
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp->env);
		free(tmp);
	}
}
