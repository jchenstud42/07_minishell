/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <jchen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:44:54 by jchen             #+#    #+#             */
/*   Updated: 2024/12/16 16:57:15 by jchen            ###   ########.fr       */
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

/*
[ < : INPUT(1) ] [ << : HEREDOC(2) ] [ >> : APPEND(3) ] [ > : OUTPUT(4) ]
*/
enum				e_token_list
{
	INPUT = 1,
	HEREDOC,
	APPEND,
	OUTPUT,
	PIPE,
	CMD,
	ARG
};

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
	char			*cmd_path;
	int				infile;
	int				outfile;
	char			*filename;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct global
{
	char			*line;
	char			*arg;
	int				exit_value;
	char			**env_array;
	char			*temp_str;
	t_token			*token_list;
	t_env			*env_list;
	t_cmd			*cmd_list;
}					t_global;

// BUILTINS_UTILS.C
void				ft_swap_tab(int i, int j, char **tab);
int					env_len(t_env *env);
void				prepare_builtin(t_cmd *cmd_list, t_global *global);
void				permission_denied_message(char *error_msg,
						t_global *global);

// CD.C
void				cd_print_error_message(char *error_msg, t_global *global);
void				update_oldpwd(t_global *global);
void				update_pwd(t_global *global);
int					ft_cd(t_global *global, char **cmd_list);
int					cd_home(t_global *global);

// ECHO.C
int					check_n(char *line);
void				print_echo(int nbr_caract, int i, char **cmd_list);
int					ft_echo(t_global *global, char **cmd_list);

// ENV.C
int					ft_env(t_global *global, t_env *env);
void				check_env(t_env **env, t_env *tmp);
void				sort_env(char **tab, int len);

// EXIT.c
void				ft_exit(t_global *global, char **cmd_args);

// EXPORT_UTILS.c
int					export_no_arg(t_env *env);
int					export_syntaxe(char *line);

// EXPORT.c
int					ft_export(t_global *global, t_env **env, char **line);

// PWD.c
int					ft_pwd(t_global *global);

// UNSET.c
int					validate_unset_cmd(char *cmd);
int					env_exist(t_env *env, char *cmd);
void				remove_env_entry(t_env **env, int exist);
int					unset(t_env **env, char *cmd);
int					ft_unset(t_global *global, t_env **env, char **cmd);

// ENV_UTILS.c
int					env_add_node(t_env **env, char *value);
t_env				*find_last_node_env(t_env *env);
int					check_env_line_exist(t_env *env, char *line);
int					update_env(t_env **env, char *line);

// ENV_UTILS2.c
char				*ft_strchr_env_name(char *dest, char *src);
char				*get_env_value(t_env *find_env, char *name_env);
char				*ft_strndup(const char *s, int n);

// GET_ENV.c
char				**get_env(t_env *env);

// EXEC_UTILS.c
void				status_child(t_global *global, pid_t pid);
void				catch_signals(t_global *global);
bool				check_env_path_exists(t_global *global, char **env_cpy,
						t_cmd *cmd_list);
bool				check_valid_type(t_token *token_list, t_cmd *cmd_list);
t_cmd				*last_element_of_cmd_list(t_cmd *cmd_list);

// EXECVE.c
char				*get_command_path(const char *cmd);
void				execute_command(t_global *global, t_cmd *cmd_list,
						t_env **env);

// HEREDOC.c
int					in_heredoc(int fd, char *word);
int					ft_heredoc(t_global *global, char *word, t_cmd *cmd);

// INIT_CMD.c
void				append_node_to_cmd_list(t_cmd **cmd);
char				**fill_cmd_args(t_token *token_list);
void				fill_cmd_node(t_cmd **cmd, t_token *current_token);
void				init_cmd_list(t_cmd **cmd, t_token **token);

// LAUNCH_LINE.c
bool				pipe_inside_token_list(t_global *global);
void				launch_line(t_global *global, t_env **env);

// PIPE.c
void				handle_redirections_pipe(t_cmd *cmd, int input_fd,
						int *fds);
void				parent_process(int *fds, int *backup_fd, pid_t pid);
void				child_process(t_cmd *cmd, int *fds, t_global *global,
						int input_fd);
void				execute_pipe(t_cmd *cmd, t_global *global);

// EXIT_FUNCTION.c
void				exit_function(t_global *global, bool write_exit);
void				free_all(t_global *global_data);

// FREE.c
void				free_array(char **array);
void				free_token_list(t_token **token_list);
void				free_cmd_list(t_cmd **cmd_list);
void				free_env_list(t_env *env);

// CHECK_LINE.c
bool				invalid_first_token(t_global *global, t_token *token_list);
bool				check_in_first_token(t_global *global, t_token *token_list);
int					check_line(t_global *global, t_token *token_list);

// CHECK_LINE2.c
bool				slash_in_cmd_token(char *token, bool print_msg);
bool				is_point_and_slash(char *token, t_global *global);
bool				pipe_after_pipe(t_global *global, t_token *token);

// COUNT.c
int					count_pipe(char *line);
int					count_cmd_token(t_token *token_list);

// DOLLAR_UTILS.c
void				ft_dollar_question(t_global *global);
char				*ft_strcharjoin(char const *str, char c);
char				*free_and_strcharjoin(char **result, char c);

// DOLLAR.c
char				*dollar_parsing(t_global *global, char *line);

// REDIRECTION.c
bool				last_token_redirection(t_token *token_list);
bool				invalid_redirection(t_token *token_list, t_global *global);
bool				tok_is_redir(t_token *token);
bool				str_is_redirection(char *str);

// REDIRECTION_2.c
// int					handle_redirection(t_global *global,
// t_token *token_list);
int					handle_redirection(t_global *global, t_cmd *cmd);
int					redirect(char *filename, int mode, int std_fd);

// SPECIAL_TOKEN.c
int					is_builtin(char *cmd);
int					char_is_pipe(char c);
bool				token_is_special_token(t_token *token);
int					str_is_special_token(char *token);

// SIGNAL.c
void				sig_c(int sig);
void				handle_nl(int sig);
void				sig_heredoc(int sig);
void				init_signals(t_global *global);

// INIT_TOKEN_LIST.c
t_token				*last_element_of_list(t_token *token_list);
int					check_token_type(char *token, t_token *last_node);
void				append_node_to_token_list(t_global **global, char *prompt);

// TOKEN_UTILS.c
int					is_white_space(char c);
void				skip_beginning_white_space(int *end, char *line);
int					nbr_arg_after_cmd(t_token *token_list);
bool				quotes_are_closed(char *line);

// TOKENIZE_LINE.c
void				line_tokenization(t_global **global, char **line);

// INITIALIZATION.c
void				calloc_global_struct(t_global **global_data);
char				**fill_arg_after_cmd(t_token *token_list);
void				init_env_list(t_env **env_to_add, char **env);
void				init_env(t_env *env_list);

#endif
