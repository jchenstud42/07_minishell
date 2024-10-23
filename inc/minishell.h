/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:25:12 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/23 10:06:03 by rbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

enum				error_number
{
	STRUCT_INIT_FAILED,
	TOKENIZATION_FAILED,
	STRUCT_NOT_INITIALIZED,
	EMPTY_LINE,
	MALLOC_FAILED
};

enum				token_list
{
	INPUT = 1, //"<"
	HEREDOC,   //"<<"
	TRUNC,     //">"
	APPEND,    //">>"
	PIPE,      //"|"
	CMD,       //"echo"
	ARG        //"bonjour"
};

# define TRUE 1
# define FALSE 0
# define ERROR -1

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

typedef struct global
{
	char			*line;
	t_token			*token_list;
}					t_global;


// CD

// ECHO
void				print_echo(int nbr_caract, char **av);
void				ft_echo(char **av);
bool				check_n(char *line);

// ENV
bool				ft_env(t_env *env);
void				check_env(t_env **env, t_env *tmp);

//EXIT

//EXPORT

// PWD
bool				ft_pwd(void);

// ERROR_HANDLER.c
void				error_handler(int nb, t_global *global_data);

//EXEC.C

int					is_builtins(char *cmd);

// CHECK_LINE.c
int					count_pipe(char *line);
int					quote_are_closed(char *line);

// IS_SPECIAL_TOKEN.c
bool				is_redirection(char *str);
bool				is_pipe(char *str);

// initialization.c
void				calloc_global_struct(t_global **global_data);

// init_token_list.c
t_token				*last_element_of_list(t_token *token_list);
void				append_node_to_token_list(t_global **global, char *prompt);

//TOKEN_UTILS.c

bool				is_white_space(char c);

// tokenize_line.c
void				stock_line(t_global **global, char *line);

// A RETIRER PLUS TARD
void				append_token_node_test(t_global **global, char *prompt);



// free.c
void				free_token_list(t_token **token_list);
void				free_all(t_global *global_data);
#endif
