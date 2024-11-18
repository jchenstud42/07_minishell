/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/11/18 13:15:12 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/18 13:15:12 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


// Verifie si le caractere est un espace blanc ou un guillement
// int	is_white_space_or_quotes(char c)
// {
// 	return (((9 <= c) && (c <= 13)) || (c == 32) || (c == '\'') || (c == '"'));
// }

int	is_white_space(char c)
{
	return (((9 <= c) && (c <= 13)) || (c == 32));
}

// Compte le nombre d'ARG se trouvant apres une CMD
int	nbr_arg_after_cmd(t_token *token_list)
{
	int nbr_arg;
	t_token *current_token;

	nbr_arg = 1;
	if (!token_list)
		return (perror("error, empty token list"), -1);
	current_token = token_list->next;
	while (current_token && current_token->type == ARG)
	{
		current_token = current_token->next;
		nbr_arg++;
	}
	return (nbr_arg);
}
