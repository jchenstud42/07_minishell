/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouquet <rbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:25:12 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/25 11:32:37 by rbouquet         ###   ########.fr       */
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
# include <limits.h>

enum				e_error_number
{
	STRUCT_INIT_FAILED,
	TOKENIZATION_FAILED,
	STRUCT_NOT_INITIALIZED,
	EMPTY_LINE,
	MALLOC_FAILED,
	ERROR_TOKEN_TYPE_ATTRIBUTION
};

enum				e_token_list
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
	int				token_count;
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

// CD.c

// ECHO.c
void				print_echo(int nbr_caract, char **av);
void				ft_echo(char **av);
bool				check_n(char *line);

// ENV.c
bool				ft_env(t_env *env);
void				check_env(t_env **env, t_env *tmp);

// EXIT.c

// EXPORT.c

// PWD.c
bool				ft_pwd(void);

// UNSET.c

bool				unset_syntaxe(char *av);

// ERROR_HANDLER.c
void				error_handler(int nb, t_global *global_data);

// EXEC.C
int					is_builtins(char *cmd);

// CHECK_LINE.c
int					count_pipe(char *line);
int					quote_are_closed(char *line);

// IS_SPECIAL_TOKEN.c
bool				is_redirection(char *str);
bool				is_pipe(char *str);

// INITIALIZATION.c
void				calloc_global_struct(t_global **global_data);

// INIT_TOKEN_LIST.c
t_token				*last_element_of_list(t_token *token_list);
int					check_token_type(char *token, t_token *last_node,
						t_global **global);
void				append_node_to_token_list(t_global **global, char *prompt);

// TOKEN_UTILS.c
int					is_white_space(char c);

// TOKENIZE_LINE.c
void				stock_line(t_global **global, char *line);
void				line_tokenization(t_global **global, int ac, char **av);

// FREE.c
void				free_token_list(t_token **token_list);
void				free_all(t_global *global_data);

#endif
