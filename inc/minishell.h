/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:25:12 by rbouquet          #+#    #+#             */
/*   Updated: 2024/10/31 11:26:44 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

enum				e_error_number
{
	STRUCT_INIT_FAILED,
	TOKENIZATION_FAILED,
	STRUCT_NOT_INITIALIZED,
	EMPTY_LINE,
	MALLOC_FAILED,
	ERROR_TOKEN_TYPE_ATTRIBUTION,
	FORK_FAILED,
	COMMAND_NOT_FOUND,
	EXECVE_FAILED
};

enum				e_token_list
{
	INPUT = 1,
	HEREDOC,
	TRUNC,
	APPEND,
	PIPE,
	CMD,
	ARG
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
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct global
{
	char			*line;
	t_token			*token_list;
	t_env			*env;
}					t_global;

// BUILTINS_UTILS.c
void				ft_swap_tab(int i, int j, char **tab);
int					env_len(t_env *env);

// CD.c

// ECHO.c
void				print_echo(int nbr_caract, char **av);
void				ft_echo(char **av);
int					check_n(char *line);

// ENV.c
int					ft_env(t_env *env);
void				check_env(t_env **env, t_env *tmp);
void				sort_env(char **tab, int len);

// EXIT.c

// EXPORT.c

int					export_no_arg(t_env *env);
int					export_syntaxe(char *line);
int					ft_export(t_env **env, char **line);

// PWD.c
int					ft_pwd(void);

// UNSET.c
int					unset_syntaxe(char *av);

// ENV_UTILS.c
int					env_add_node(t_env **env, char *value);
t_env				*find_last_node_env(t_env *env);

// GET_ENV.c
char				**get_env(t_env *env);

// EXEC.C
void				launch_line(t_global *global, char **env);

// EXECVE.C
char				*get_command_path(const char *cmd, t_global *global);
int					nbr_arg_after_cmd(t_global *global);
char				**fill_execve_arg_array(t_global *global);
void				execute_command(char *cmd, char **env, t_global *global);

// FREE.c
void				free_token_list(t_token **token_list);
void				free_array(char **array);
void				free_env_list(t_env *env);
void				free_all(t_global *global_data);

// CHECK_LINE.c
int					count_pipe(char *line);
int					quote_are_closed(char *line);
int					first_token_pipe(t_token *token_list);
int					last_token_redirection(t_token *token_list);
int					check_line(t_global *global, t_token *token_list);

// IS_SPECIAL_TOKEN.c
int					is_builtin(char *cmd);
int					is_redirection(char *str);
int					is_pipe(char *str);

// SIGNAL.c
void				sig_c(int sig);
void				init_signals(void);

// INIT_TOKEN_LIST.c
t_token				*last_element_of_list(t_token *token_list);
int					check_token_type(char *token, t_token *last_node,
						t_global **global);
void				append_node_to_token_list(t_global **global, char *prompt);

// TOKEN_UTILS.c
int					is_white_space(char c);

// TOKENIZE_LINE.c
void				stock_line(t_global **global, char *line);
void				line_tokenization(t_global **global, char *line);

// ERROR_HANDLER.c
void				error_handler(int nb, t_global *global_data);

// INITIALIZATION.c
void				calloc_global_struct(t_global **global_data);









#endif
