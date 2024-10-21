/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:25:12 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/21 09:57:56 by rbouquet         ###   ########.fr       */
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

enum				error_number
{
	TOKENIZATION_FAILED,
	PROBLEM2
};

// Type de token
# define INPUT 1 //"<"
# define HEREDOC 2 //"<<"
# define TRUNC 3 //">"
# define APPEND 4 //">>"
# define PIPE 5 //"|"
# define CMD 6 //"echo"
# define ARG 7 //"bonjour"

// J'ai mis l'index(/position) pour le moment, a voir si c'est necessaire
typedef struct s_token
{
	char			*token;
	int				index;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_env
{
	char			*env;
	char			*str;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

// NEXT et PREV a mettre dans une autre structure plus tard pour plus boooooooo
typedef struct global
{
	char			*line;
	t_token			token_list;
}					t_global;

// Deso Romaingue, quand je sauvegarde ca enleve les tabs :(((
// SRC
// BUILTING
// CD

// ECHO
void				print_echo(int nbr_caract, char **av);
void				ft_echo(char **av);
int					check_n(char *line);

// init_token.c
void				append_token_node(t_token **token_list, char *prompt);

// error_handler.c
void				error_handler(int nb, t_global *global_data);

// free.c
void				free_token_list(t_token **token_list);
void				free_all(t_global *global_data);
#endif
