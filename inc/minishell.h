/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/11/08 15:59:34 by jchen             #+#    #+#             */
/*   Updated: 2024/11/08 15:59:34 by jchen            ###   ########.fr       */
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

# define GREEN "\001\033[1;32m\002"
# define RESET "\001\033[0m\002"

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
	char			*value;
	char			*name;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct s_cmd
{
	char			*cmd;
	char			**cmd_args;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct global
{
	char			*line;
	char			*arg;
	int				exit_value;
	t_token			*token_list;
	t_env			*env_list;
	t_cmd			*cmd_list;
}					t_global;

// BUILTINS_UTILS.C
void				ft_swap_tab(int i, int j, char **tab);
int					env_len(t_env *env);
void				execute_builtin(t_cmd *cmd_list, t_global *global);

// CD.C
void				cd_print_error_message(char *error_msg);
int					update_oldpwd(t_global *global);
void				update_pwd(t_global *global);
int					ft_cd(t_global *global, char **cmd_list);
int					cd_home(t_global *global);

// ECHO.C
int					check_n(char *line);
void				print_echo(int nbr_caract, int i, char **cmd_list);
int					ft_echo(char **cmd_list);

// ENV.C
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
int					check_env_line_exist(t_env *env, char *line);
int					update_env(t_env **env, char *line);

// ENV_UTILS2.c
char				*ft_strchr_env_name(char *dest, char *src);
char				*get_env_value(t_env *find_env, char *name_env);

// GET_ENV.c
char				**get_env(t_env *env);

// EXEC.c
bool				pipe_inside_token_list(t_global *global);
void				launch_line(t_global *global, char **env);

// EXECVE.c
char				*get_command_path(const char *cmd);
void				execute_command(t_cmd *cmd_list, char **env);

// INIT_CMD.c
t_cmd				*last_element_of_cmd_list(t_cmd *cmd_list);
void				append_node_to_cmd_list(t_cmd **cmd, char *cmd_token);
char				**fill_cmd_args(t_token *token_list);
void				fill_cmd_node(t_cmd **cmd, t_token *current_token);
void				init_cmd_list(t_cmd **cmd, t_token **token);

// PIPE.c
void				handle_redirections(t_cmd *cmd, int input_fd, int *fds);
void				parent_process(int *fds, int *backup_fd, pid_t pid);
void				child_process(t_cmd *cmd, int *fds, t_global *global,
						char **env, int input_fd);
void				execute_pipe(t_cmd *cmd, char **env, t_global *global);

// FREE.c
void				free_array(char **array);
void				free_token_list(t_token **token_list);
void				free_cmd_list(t_cmd **cmd_list);
void				free_env_list(t_env *env);
void				free_all(t_global *global_data);

// CHECK_LINE.c
bool				invalid_first_token(t_token *token_list);
bool				last_token_redirection(t_token *token_list);
bool				slash_in_cmd_token(char *token, bool print_msg);
int					check_line(t_global *global, t_token *token_list);

// COUNT.c
int					count_pipe(char *line);
int					count_cmd_token(t_token *token_list);

// SPECIAL_TOKEN.c
int					is_builtin(char *cmd);
int					is_special_token(char *token);
int					is_redirection(char *str);
int					is_pipe(char c);

// SIGNAL.c
void				sig_c(int sig);
void				handle_nl(int sig);
void				init_signals(void);

// INIT_TOKEN_LIST.c
t_token				*last_element_of_list(t_token *token_list);
int					check_token_type(char *token, t_token *last_node);
void				append_node_to_token_list(t_global **global, char *prompt);

// TOKEN_UTILS.c
int					is_white_space(char c);
int					nbr_arg_after_cmd(t_token *token_list);

// TOKENIZE_LINE.c
char				*line_quote_manager(char *line);
void				add_special_token(t_global *global, char *line, int *end);
void				line_tokenization(t_global **global, char *line);

// ERROR_HANDLER.c //////// A RETIRER
void				error_handler(int nb, t_global *global_data);

// INITIALIZATION.c
void				calloc_global_struct(t_global **global_data);
char				**fill_arg_after_cmd(t_token *token_list);
void				init_env_list(t_env **env_to_add, char **env);
void				init_env(t_env *env_list);

#endif
