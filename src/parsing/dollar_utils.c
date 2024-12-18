/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:24:44 by rbouquet          #+#    #+#             */
/*   Updated: 2024/12/18 09:24:45 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_dollar_question(t_global *global)
{
	printf("minishell: %d: command not found\n", global->exit_value);
	global->exit_value = 127;
}

char	*ft_strcharjoin(char const *str, char c)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	res = malloc((ft_strlen(str) + 2) * sizeof(char));
	if (!res)
		return (NULL);
	while (str[i])
		res[j++] = str[i++];
	res[j++] = c;
	res[j] = '\0';
	return (res);
}

char	*free_and_strcharjoin(char **result, char c)
{
	char	*temp;

	temp = ft_strcharjoin(*result, c);
	if (!temp)
	{
		free(*result);
		return (perror("error, strcharjoin failed"), NULL);
	}
	if (*result)
		free(*result);
	*result = temp;
	temp = NULL;
	return (*result);
}
