/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:17:03 by jchen             #+#    #+#             */
/*   Updated: 2024/12/07 12:13:36 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// OLD ///////////////////////////////////////////////////////////////////

static char	*dollar_question(char *result, t_global *global, int *i)
{
	char	*itoa_exit_value;
	char	*temp;

	itoa_exit_value = ft_itoa(global->exit_value);
	if (!itoa_exit_value)
		return (perror("error, malloc itoa exit value failed"), NULL);
	temp = ft_strjoin(result, itoa_exit_value);
	if (!temp)
		return (perror("error, malloc failed in ft_strjoin"), NULL);
	(*i) += 2;
	free(itoa_exit_value);
	free(result);
	return (temp);
}

static char	*search_dollar_env_value(char *result, char *dollar_token,
		t_env *env)
{
	t_env	*env_cpy;
	char	*str;

	env_cpy = env;
	str = NULL;
	while (env_cpy)
	{
		if (!ft_strcmp(dollar_token, env_cpy->name))
		{
			str = ft_strjoin(result, env_cpy->value);
			if (!str)
				return (perror("error, strjoin dollar env failed"), NULL);
			break ;
		}
		env_cpy = env_cpy->next;
	}
	return (str);
}

static char	*dollar_env(int *i, t_global *global, char **result)
{
	char	*dollar_env_name;
	char	*dollar_env_value;
	int		k;

	dollar_env_value = NULL;
	dollar_env_name = ft_calloc(1000, sizeof(char));
	if (!dollar_env_name)
		return (perror("Error, dollar_token malloc"), NULL);
	k = ++(*i);
	while (ft_isalnum(global->line[k]))
		k++;
	ft_strlcpy(dollar_env_name, &global->line[*i], k - (*i) + 1);
	(*i) = k;
	dollar_env_value = search_dollar_env_value(*result, dollar_env_name,
			global->env_list);
	if (!dollar_env_value)
		return (free(dollar_env_name), *result);
	free(*result);
	*result = dollar_env_value;
	return (free(dollar_env_name), dollar_env_value);
}

static char	*translate_dollar_sign(t_global *global, char *result, int *i,
		bool double_quotes)
{
	if (global->line[(*i) + 1] == '?')
		result = dollar_question(result, global, i);
	else if (ft_isdigit(global->line[(*i) + 1]))
		(*i) += 2;
	else if (global->line[(*i) + 1] == '\'' && global->line[(*i) + 2] != '\'')
	{
		while (global->line[++(*i)] != '\'')
			result = free_and_strcharjoin(&result, global->line[(*i)++]);
	}
	else if (global->line[(*i) + 1] == '"' && !double_quotes
		&& global->line[(*i) + 2] != '"')
	{
		while (global->line[++(*i)] != '"')
			result = free_and_strcharjoin(&result, global->line[(*i)++]);
	}
	else if (is_white_space(global->line[(*i) + 1])
		|| (!ft_isalnum(global->line[(*i) + 1]) && global->line[(*i)
			+ 2] != '\'' && global->line[(*i) + 2] != '"'))
	{
		result = free_and_strcharjoin(&result, '$');
		(*i)++;
	}
	else
		result = dollar_env(i, global, &result);
	return (result);
}

char	*dollar_parsing(t_global *global, char *line)
{
	int		i;
	char	*result;
	bool	single_quotes;
	bool	double_quotes;

	i = 0;
	single_quotes = false;
	double_quotes = false;
	result = ft_calloc(1000, sizeof(char));
	if (!result)
		return (perror("Error,  result malloc"), NULL);
	while (line[i])
	{
		if (line[i] == '\'')
			single_quotes = !single_quotes;
		else if (line[i] == '"')
			double_quotes = !double_quotes;
		if (!single_quotes && line[i + 1] && line[i] == '$')
			result = translate_dollar_sign(global, result, &i, double_quotes);
		else
			result = free_and_strcharjoin(&result, line[i++]);
	}
	free(line);
	return (result);
}

// ESSAI 1 : TROP DE PBS ////////////////////////////////////////////////////
//
// static char	*dollar_question(char *result, t_global *global, int *i)
// {
// 	char	*itoa_exit_value;

// 	itoa_exit_value = ft_itoa(global->exit_value);
// 	if (!itoa_exit_value)
// 		return (perror("error, malloc itoa exit value failed"), NULL);
// 	if (global->temp_str)
// 	{
// 		free(global->temp_str);
// 		global->temp_str = NULL;
// 	}
// 	global->temp_str = ft_strjoin(result, itoa_exit_value);
// 	if (!global->temp_str)
// 		return (perror("error, malloc failed in ft_strjoin"),
// 				free(itoa_exit_value),
// 				NULL);
// 	(*i) += 2;
// 	free(itoa_exit_value);
// 	free(result);
// 	return (global->temp_str);
// }

// static char	*search_dollar_env_value(char *result, char *dollar_token,
// 		t_global *global)
// {
// 	t_env	*env_cpy;

// 	env_cpy = global->env_list;
// 	while (env_cpy)
// 	{
// 		if (!ft_strcmp(dollar_token, env_cpy->name))
// 		{
// 			if (global->temp_str)
// 			{
// 				free(global->temp_str);
// 				global->temp_str = NULL;
// 			}
// 			global->temp_str = ft_strjoin(result, env_cpy->value);
// 			if (!global->temp_str)
// 				return (perror("error, strjoin dollar_env"), NULL);
// 			break ;
// 		}
// 		env_cpy = env_cpy->next;
// 	}
// 	if (global->temp_str)
// 	{
// 		free(result);
// 		result = global->temp_str;
// 		return (global->temp_str);
// 	}
// 	return (result);
// }

// static char	*dollar_env(int *i, t_global *global, char *result)
// {
// 	char	*dollar_env_name;
// 	char	*dollar_env_value;
// 	int		k;

// 	dollar_env_value = NULL;
// 	dollar_env_name = ft_calloc(1000, sizeof(char));
// 	if (!dollar_env_name)
// 		return (perror("Error, dollar_token malloc"), NULL);
// 	k = ++(*i);
// 	while (ft_isalnum(global->line[k]))
// 		k++;
// 	ft_strlcpy(dollar_env_name, &global->line[*i], k - (*i) + 1);
// 	(*i) = k;
// 	dollar_env_value = search_dollar_env_value(result, dollar_env_name, global);
// 	if (!dollar_env_value)
// 		return (free(dollar_env_name), result);
// 	return (free(dollar_env_name), dollar_env_value);
// }

// static char	*translate_dollar_sign(t_global *global, char *result, int *i,
// 		bool double_quotes)
// {
// 	if (global->line[(*i) + 1] == '?')
// 		result = dollar_question(result, global, i);
// 	else if (ft_isdigit(global->line[(*i) + 1]))
// 		(*i) += 2;
// 	else if (global->line[(*i) + 1] == '\'' && global->line[(*i) + 2] != '\'')
// 	{
// 		while (global->line[++(*i)] != '\'')
// 			result = free_and_strcharjoin(&result, global->line[(*i)++]);
// 	}
// 	else if (global->line[(*i) + 1] == '"' && !double_quotes
// 			&& global->line[(*i) + 2] != '"')
// 	{
// 		while (global->line[++(*i)] != '"')
// 			result = free_and_strcharjoin(&result, global->line[(*i)++]);
// 	}
// 	else if (is_white_space(global->line[(*i) + 1])
// 			|| (!ft_isalnum(global->line[(*i) + 1]) && global->line[(*i)
// 				+ 2] != '\'' && global->line[(*i) + 2] != '"'))
// 	{
// 		result = free_and_strcharjoin(&result, '$');
// 		(*i)++;
// 	}
// 	else
// 		result = dollar_env(i, global, result);
// 	return (result);
// }

// char	*dollar_parsing(t_global *global, char *line)
// {
// 	int		i;
// 	char	*result;
// 	bool	single_quotes;
// 	bool	double_quotes;

// 	i = 0;
// 	single_quotes = false;
// 	double_quotes = false;
// 	result = ft_calloc(1000, sizeof(char));
// 	if (!result)
// 		return (perror("Error,  result malloc"), NULL);
// 	while (line[i])
// 	{
// 		if (line[i] == '\'')
// 			single_quotes = !single_quotes;
// 		else if (line[i] == '"')
// 			double_quotes = !double_quotes;
// 		if (!single_quotes && line[i + 1] && line[i] == '$')
// 			result = translate_dollar_sign(global, result, &i, double_quotes);
// 		else
// 			result = free_and_strcharjoin(&result, line[i++]);
// 	}
// 	return (result);
// }
