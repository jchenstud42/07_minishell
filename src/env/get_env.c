/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:02:24 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/30 14:07:09 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Replique la commande env (vite fait)
// int	getenv_example(void)
// {
// 	const char	*home;

// 	home = getenv("HOME");
// 	if (!home)
// 		return (1);
// 	printf("HOME=%s\n", home);
// 	return (0);
// }

// Replique MIEUX la commande env, en prenant en parametre env
// int	getenv_false_example(char **env)
// {
// 	char	**print_env;

// 	print_env = env;
// 	while (*print_env)
// 	{
// 		ft_printf("%s\n", *print_env);
// 		print_env++;
// 	}
// 	return (0);
// }

char	**get_env(t_env *env)
{
	t_env	*env_size;
	char	**env_tab;
	int		i;

	i = 0;
	env_size = env;
	while (env_size)
	{
		i++;
		env_size = env_size->next;
	}
	env_tab = malloc(sizeof(char *) * (i + 1));
	if (!env_tab)
		return (NULL);
	env_size = env;
	i = 0;
	while (env_size)
	{
		env_tab[i++] = env_size->env;
		env_size = env_size->next;
	}
	env_tab[i] = NULL;
	return (env_tab);
}

t_env	*create_env_node(const char *str)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->env = strdup(str);
	new_node->next = NULL;
	return (new_node);
}

// Fonction de test pour get_env
// void	test_get_env(void)
// {
// 	t_env	*env1 = create_env_node("PATH=/usr/bin");
// 	t_env	*env2 = create_env_node("HOME=/home/user");
// 	t_env	*env3 = create_env_node("SHELL=/bin/bash");
// 	char	**env_tab;
// 	int		i;

// 	i = 0;
// 	env1->next = env2;
// 	env2->next = env3;
// 	env_tab = get_env(env1);
// 	if (env_tab)
// 	{
// 		ft_printf("Test de get_env:\n");
// 		while (env_tab[i])
// 		{
// 			ft_printf("env_tab[%d]: %s\n", i, env_tab[i]);
// 			i++;
// 		}
// 	}
// 	else
// 		ft_printf("Erreur : get_env a retourné NULL\n");
// 	free(env_tab);
// 	free_env_list(env1);
// }
