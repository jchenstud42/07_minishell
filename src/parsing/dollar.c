/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:15:27 by jchen             #+#    #+#             */
/*   Updated: 2024/11/24 13:01:01 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_dollar_sign(t_global *global)
{
	printf("minishell: %d: command not found\n", global->exit_value);
}

static int	ft_intlen_exit(int nbr)
{
	int	digit_nbr;

	if (!nbr)
		return (0);
	digit_nbr = 1;
	while (nbr >= 10)
	{
		nbr /= 10;
		digit_nbr++;
	}
	return (digit_nbr);
}

char	*dollar_interpretation(t_global *global, t_env *env, char *line)
{
	int		i;
	int		j;
	int		k;
	char	*result;
	char	*dollar_token;
	t_env	*env_cpy;
	bool	single_quotes;

	i = 0;
	j = 0;
	k = 0;
	single_quotes = false;
	dollar_token = malloc(1000);
	result = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	if (!result || !dollar_token)
		return (perror("error, line dollar malloc failed"), NULL);
	global->exit_value = 666;
	while (line[i])
	{
		if (line[i] == '\'')
			single_quotes = !single_quotes;
		if (single_quotes == false && line[i] == '$')
		{
			if (line[i + 1] == '?')
			{
				result = ft_strjoin(result, ft_itoa(global->exit_value));
				j += ft_intlen_exit(global->exit_value);
				printf("$? : %s\n", result);
				i += 2;
				result[j++] = line[i];
			}
			else
			{
				if (!ft_isalnum(line[i + 1]))
				{
					result[j] = '$';
					j++;
					printf("$ non alphanum : %s\n", result);
				}
				i++;
				k = i;
				while (ft_isalnum(line[k]))
					k++;
				ft_strlcpy(dollar_token, &line[i], k - i + 1);
				i = k - 1;
				printf("dollar_token : %s\n", dollar_token);
				env_cpy = env;
				while (env_cpy)
				{
					if (!ft_strcmp(dollar_token, env_cpy->name))
					{
						printf("env name : %s\n", env_cpy->value);
						result = ft_strjoin(result, env_cpy->value);
						j += ft_strlen(env_cpy->value);
						break ;
					}
					env_cpy = env_cpy->next;
				}
			}
		}
		else
			result[j++] = line[i];
		i++;
	}
	free(dollar_token);
	result[j] = '\0';
	printf("lenght : %d\n", j);
	printf("result : %s\n", result);
	free(result);
	return (NULL);
}
