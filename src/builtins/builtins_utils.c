/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:42:28 by jchen             #+#    #+#             */
/*   Updated: 2024/12/14 17:00:13 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_swap_tab(int i, int j, char **tab)
{
	char	*tmp;

	tmp = tab[i];
	tab[i] = tab[j];
	tab[j] = tmp;
}

int	env_len(t_env *env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

static void	builtin_execution(t_cmd *cmd_list, t_global *global)
{
	if (ft_strcmp(cmd_list->cmd, "cd") == 0)
		ft_cd(global, cmd_list->cmd_args);
	else if (ft_strcmp(cmd_list->cmd, "echo") == 0)
		ft_echo(global, cmd_list->cmd_args);
	else if (ft_strcmp(cmd_list->cmd, "env") == 0)
		ft_env(global, global->env_list);
	else if (ft_strcmp(cmd_list->cmd, "exit") == 0)
		ft_exit(global, cmd_list->cmd_args);
	else if (ft_strcmp(cmd_list->cmd, "export") == 0)
		ft_export(global, &global->env_list, cmd_list->cmd_args);
	else if (ft_strcmp(cmd_list->cmd, "pwd") == 0)
		ft_pwd(global);
	else if (ft_strcmp(cmd_list->cmd, "unset") == 0)
		ft_unset(global, &global->env_list, cmd_list->cmd_args);
	else if (ft_strcmp(cmd_list->cmd, "$?") == 0)
		ft_dollar_question(global);
}

void	execute_builtin(t_cmd *cmd_list, t_global *global)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
		return (perror("dup sauvegarde"));
	if (global->cmd_list->outfile_cmd != -1)
		dup2(global->cmd_list->outfile_cmd, STDOUT_FILENO);
	if (global->cmd_list->infile_cmd != -1)
		dup2(global->cmd_list->infile_cmd, STDIN_FILENO);
	builtin_execution(cmd_list, global);
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		perror("Restauration stdin");
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		perror("Restauration stdout");
	close(saved_stdin);
	close(saved_stdout);
}
