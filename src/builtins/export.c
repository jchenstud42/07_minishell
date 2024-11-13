/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:02:48 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/13 14:00:08 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	export_no_arg(t_env *env)
{
	char	**env_tab;
	int		i;
	int		j;

	env_tab = get_env(env);
	if (!env_tab)
		return (1);
	sort_env(env_tab, env_len(env));
	i = 0;
	while (env_tab[i])
	{
		j = 0;
		ft_printf("declare -x ");
		while (env_tab[i][j] && env_tab[i][j] != '=')
			ft_printf("%c", env_tab[i][j++]);
		if (env_tab[i][j] && env_tab[i][j] == '=')
			ft_printf("=\"%s\"\n", &env_tab[i][j++]);
		else
			ft_printf("\n");
		i++;
	}
	free(env_tab);
	return (0);
}

int	export_syntaxe(char *line)
{
	int	i;

	i = 0;
	if (!line[0] || (line[0] != '_' && !ft_isalpha(line[0])))
		return (0);
	while (line[i] && line[i] != '=')
	{
		if (line[i] != '_' && !ft_isalnum(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(t_env **env, char **line)
{
	int	i;

	i = 1;
	if (!line[i])
	{
		if (*env && !export_no_arg((*env)))
			return (1);
		return (0);
	}
	while (line[i])
	{
		if (!export_syntaxe(line[i]))
		{
			ft_putstr_fd("bash: export: '", 2);
			ft_putstr_fd(line[i], 2);
			ft_putstr_fd("': invalid identifier\n", 2);
			return (1);
		}
		if (update_env(env, line[i]))
			return (1);
		i++;
	}
	return (0);
}

// void test_ft_export() {
// 	// 1. Création de l'environnement initial
// 	t_env *env1 = create_env_node("PATH=/usr/bin");
// 	t_env *env2 = create_env_node("HOME=/home/user");
// 	env1->next = env2;
// 	t_env *env_list = env1;

// 	// Cas 1 : Aucun argument (doit appeler export_no_arg pour afficher l'environnement)
// 	printf("Cas 1 : Appel sans argument\n");
// 	char *args1[] = {"export", NULL};
// 	ft_export(&env_list, args1);

// 	// Cas 2 : Ajout d'une variable d'environnement valide
// 	printf("\nCas 2 : Ajout d'une variable d'environnement valide\n");
// 	char *args2[] = {"export", "USER=newuser", NULL};
// 	ft_export(&env_list, args2);

// 	// Cas 3 : Tentative d'ajout d'une variable avec syntaxe invalide
// 	printf("\nCas 3 : Syntaxe invalide pour une variable\n");
// 	char *args3[] = {"export", "123INVALID=error", NULL};
// 	ft_export(&env_list, args3);

// 	// Cas 4 : Ajout multiple avec une combinaison valide et invalide
// 	printf("\nCas 4 : Ajout multiple, valide et invalide\n");
// 	char *args4[] = {"export", "EDITOR=vim", "3INVALID=error",
// "SHELL=/bin/bash", NULL};
// 	ft_export(&env_list, args4);

// 	// Libération de l'environnement
// 	free_env_list(env_list);
// }
