/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/10/23 09:30:04 by rbouquet          #+#    #+#             */
/*   Updated: 2024/11/06 11:22:21 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


// Verifie si le caractere est un espace blanc
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
