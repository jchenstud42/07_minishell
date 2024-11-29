/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/11/20 14:15:27 by jchen             #+#    #+#             */
/*   Updated: 2024/11/24 17:00:35 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


static char	*dollar_question(char *result, t_global *global, int *i, int *j)
{
	char *itoa_exit_value;
	char *temp;

	itoa_exit_value = ft_itoa(global->exit_value);
	if (!itoa_exit_value)
		return (perror("error, malloc itoa exit value failed"), NULL);
	temp = ft_strjoin(result, itoa_exit_value);
	if (!temp)
		return (perror("error, malloc failed in ft_strjoin"), NULL);
	(*j) += ft_strlen(itoa_exit_value);
	(*i) += 2;
	free(itoa_exit_value);
	free(result);
	return (temp);
}

static char	*search_dollar_env_value(char *result, char *dollar_token,
		t_env *env, int *j)
{
	t_env *env_cpy;
	char *str;

	env_cpy = env;
	str = NULL;
	while (env_cpy)
	{
		if (!ft_strcmp(dollar_token, env_cpy->name))
		{
			str = ft_strjoin(result, env_cpy->value);
			if (!str)
				return (perror("error, strjoin dollar env failed"), NULL);
			(*j) += ft_strlen(env_cpy->value);
			break ;
		}
		env_cpy = env_cpy->next;
	}
	return (str);
}

static char	*dollar_env(int *i, int *j, t_global *global, char *result)
{
	char *dollar_env_name;
	char *dollar_env_value;
	int k;

	dollar_env_value = NULL;
	dollar_env_name = ft_calloc(1000, sizeof(char));
	if (!dollar_env_name)
		return (perror("Error, dollar_token malloc"), NULL);
	k = ++(*i);
	while (ft_isalnum(global->line[k]))
		k++;
	ft_strlcpy(dollar_env_name, &global->line[*i], k - (*i) + 1);
	(*i) = k;
	dollar_env_value = search_dollar_env_value(result, dollar_env_name,
			global->env_list, j);
	if (!dollar_env_value)
		return (free(dollar_env_name), result);
	return (free(result), free(dollar_env_name), dollar_env_value);
}

static char	*translate_dollar_sign(t_global *global, char *result, int *i,
		int *j)
{
	if (global->line[(*i) + 1] == '?')
	{
		result = dollar_question(result, global, i, j);
		return (result);
	}
	if (ft_isdigit(global->line[(*i) + 1]))
	{
		(*i) += 2;
		return (result);
	}
	if (!ft_isalnum(global->line[(*i) + 1]))
	{
		result = ft_strcharjoin(result, '$');
		(*j)++;
		(*i)++;
		return (result);
	}
	result = dollar_env(i, j, global, result);
	return (result);
}

char	*dollar_parsing(t_global *global, char *line)
{
	int i;
	int j;
	char *result;
	bool single_quotes;

	i = 0;
	j = 0;
	single_quotes = false;
	result = ft_calloc(1000, sizeof(char));
	if (!result)
		return (perror("Error,  result malloc"), NULL);
	while (line[i])
	{
		if (line[i] == '\'')
			single_quotes = !single_quotes;
		if (single_quotes == false && line[i + 1] && line[i] == '$')
			result = translate_dollar_sign(global, result, &i, &j);
		else
		{
			result = ft_strcharjoin(result, line[i]);
			i++;
		}
	}
	return (result);
}