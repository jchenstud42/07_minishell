/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:15:27 by jchen             #+#    #+#             */
/*   Updated: 2024/11/24 17:00:35 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_dollar_sign(t_global *global)
{
	printf("minishell: %d: command not found\n", global->exit_value);
}

char	*dollar_sign(char *result, t_global *global, int *i, int *j)
{
	char	*itoa_exit_value;
	char	*temp;

	itoa_exit_value = ft_itoa(global->exit_value);
	if (!itoa_exit_value)
		return (perror("error, malloc itoa exit value failed"), NULL);
	temp = ft_strjoin(result, itoa_exit_value);
	if (!temp)
	{
		free(itoa_exit_value);
		return (perror("error, malloc failed in ft_strjoin"), NULL);
	}
	(*j) += ft_strlen(itoa_exit_value);
	printf("$? : %s\n", result);
	(*i) += 2;
	result = ft_strjoin(result, (char[]){global->line[*i], '\0'});
	// temp = ft_strjoin(temp, &global->line[*i]);
	(*j)++;
	// temp[(*j)++] = global->line[*i];
	free(result);
	free(itoa_exit_value);
	return (temp);
}

char	*check_dollar_env(int *i, int *j, t_global *global, char *result)
{
	t_env	*env_cpy;
	char	*dollar_token;
	char	*temp;
	int		k;

	// i++;
	dollar_token = ft_calloc(1000, sizeof(char));
	if (!dollar_token)
		return (perror("Error, dollar_token malloc"), NULL);
	k = ++(*i);
	while (ft_isalnum(global->line[k]))
		k++;
	ft_strlcpy(dollar_token, &global->line[*i], k - (*i) + 1);
	(*i) = k - 1;
	printf("dollar_token : %s\n", dollar_token);
	env_cpy = global->env_list;
	temp = result;
	while (env_cpy)
	{
		if (!ft_strcmp(dollar_token, env_cpy->name))
		{
			printf("env name : %s\n", env_cpy->value);
			temp = ft_strjoin(result, env_cpy->value);
			(*j) += ft_strlen(env_cpy->value);
			break ;
		}
		env_cpy = env_cpy->next;
	}
	free(result);
	return (temp);
}

char	*parse_dollar(t_global *global, char *result, int *i, int *j)
{
	if (global->line[(*i) + 1] == '?')
	{
		result = dollar_sign(result, global, i, j);
		return (result);
	}
	if (!ft_isalnum(global->line[(*i) + 1]))
	{
		result[*j] = '$';
		(*j)++;
		printf("$ non alphanum : %s\n", result);
	}
	result = check_dollar_env(i, j, global, result);
	return (result);
}

char	*dollar_interpretation(t_global *global, t_env *env, char *line)
{
	int		i;
	int		j;
	int		k;
	char	*result;
	bool	single_quotes;

	i = 0;
	j = 0;
	k = 0;
	(void)env;
	single_quotes = false;
	result = ft_calloc(1000, sizeof(char));
	if (!result)
		return (perror("Error,  result malloc"), NULL);
	global->exit_value = 666;
	while (line[i])
	{
		if (line[i] == '\'')
			single_quotes = !single_quotes;
		if (single_quotes == false && line[i] == '$')
			result = parse_dollar(global, result, &i, &j);
		else
			result = ft_strjoin(result, (char[]){line[i], '\0'});
		// result[j++] = line[i];
		i++;
	}
	// result[j] = '\0';
	printf("lenght : %zu\n", ft_strlen(result));
	printf("result : %s\n", result);
	free(result);
	return (NULL);
}

// char	*dollar_interpretation(t_global *global, t_env *env, char *line)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	char	*result;
// 	char	*dollar_token;
// 	t_env	*env_cpy;
// 	bool	single_quotes;
// 	char	*itoa_exit_value;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	single_quotes = false;
// 	dollar_token = ft_calloc(1000, sizeof(char));
// 	if (!dollar_token)
// 		return (perror("Error, dollar_token malloc"), NULL);
// 	result = ft_calloc(1000, sizeof(char));
// 	if (!result)
// 		return (perror("Error,  result malloc"), free(dollar_token), NULL);
// 	itoa_exit_value = ft_itoa(global->exit_value);
// 	if (!itoa_exit_value)
// 		return (perror("Error,  itoa exit value malloc"),
// free(dollar_token),
// 			free(result), NULL);
// 	if (!result || !dollar_token)
// 		return (perror("error, line dollar malloc failed"), NULL);
// 	global->exit_value = 666;
// 	while (line[i])
// 	{
// 		if (line[i] == '\'')
// 			single_quotes = !single_quotes;
// 		if (single_quotes == false && line[i] == '$')
// 		{
// 			if (line[i + 1] == '?')
// 			{
// 				result = ft_strjoin(result, itoa_exit_value);
// 				j += ft_intlen_exit(global->exit_value);
// 				printf("$? : %s\n", result);
// 				i += 2;
// 				result[j++] = line[i];
// 			}
// 			else
// 			{
// 				if (!ft_isalnum(line[i + 1]))
// 				{
// 					result[j] = '$';
// 					j++;
// 					printf("$ non alphanum : %s\n", result);
// 				}
// 				i++;
// 				k = i;
// 				while (ft_isalnum(line[k]))
// 					k++;
// 				ft_strlcpy(dollar_token, &line[i], k - i + 1);
// 				i = k - 1;
// 				printf("dollar_token : %s\n", dollar_token);
// 				env_cpy = env;
// 				while (env_cpy)
// 				{
// 					if (!ft_strcmp(dollar_token, env_cpy->name))
// 					{
// 						printf("env name : %s\n", env_cpy->value);
// 						result = ft_strjoin(result, env_cpy->value);
// 						j += ft_strlen(env_cpy->value);
// 						break ;
// 					}
// 					env_cpy = env_cpy->next;
// 				}
// 			}
// 		}
// 		else
// 			result[j++] = line[i];
// 		i++;
// 	}
// 	free(dollar_token);
// 	free(itoa_exit_value);
// 	result[j] = '\0';
// 	printf("lenght : %zu\n", ft_strlen(result));
// 	printf("result : %s\n", result);
// 	free(result);
// 	return (NULL);
// }
