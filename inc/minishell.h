/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:25:12 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/15 14:56:11 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// Type de token
# define INPUT 1   //"<"
# define HEREDOC 2 //"<<"
# define TRUNC 3   //">"
# define APPEND 4  //">>"
# define PIPE 5    //"|"
# define CMD 6     //"echo"
# define ARG 7     //"bonjour"

// NEXT et PREV a mettre dans une autre structure plus tard pour plus boooooooo
typedef struct global
{
	char			*line;
	struct global	*next;
	struct global	*prev;
}					t_global;

// J'ai mis l'index(/position) pour le moment, a voir si c'est necessaire
typedef struct s_token
{
	char			*token;
	int				index;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

#endif
