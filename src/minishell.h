/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:36:19 by alpetukh          #+#    #+#             */
/*   Updated: 2024/08/01 11:47:20 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "../Libft/libft.h"
# include "debug_functions/debug.h"
# include "lexer/lexer.h"
# include "expander/expander.h"
# include "parser/parser.h"
# include "wildcard/wildcard.h"
# include "helper_functions/helper_functions.h"

# define END -10
# define ALLOCFAIL -11
# define SYNTAX_ERROR 2
# define EXIT -10

// Builtin function pointer prototype
typedef void	(*t_builtin)(t_buffer*, t_lexer*);

extern int		g_signal;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef enum e_expand_code
{
	EXPANDED,
	NOT_EXPANDED
}	t_expand_code;

typedef enum e_token_type
{
	IN = 0,
	HEREDOC = 1,
	APPEND = 2,
	OUT = 3,
	PIPE = 4,
	NONE = 5,
	HEREDOC_RESOLVED = 8,
	WORD = 99,
	AND_OPERATOR = 6,
	OR_OPERATOR = 7,
	NO_OPERATOR = 8,
	PARENTHESIS_BEGIN = 9,
	PARENTHESIS_END = 10,
	NEW_LINE = 11
}	t_token_type;

typedef enum e_exit_code
{
	EXIT_BUILTIN = -2,
	NOT_EXIT = -1,
	SUCCESS = 0,
	ERROR = 1,
	MALLOC_ERROR = 2,
	FUNC_ERROR = 3,
	TEMPFILE_ERROR = 4
}	t_exit_code;

typedef enum e_strpart_type
{
	NOQUOTES = 0,
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '\"'
}	t_strpart_type;

typedef enum e_sig_mode
{
	INTERACTIVE,
	EXECUTION,
	HEREDOC_PARENT,
	HEREDOC_CHILD
}	t_sig_mode;

typedef enum e_parenthesis
{
	NO_PARE,
	FOUND_PARE,
	OPEN,
	CLOSED,
	SPACE_FOR_NEW_CMD = 1,
	SPACE_FOR_NULL_TERM = 1,
	NONE_DECREMENTED = 0,
	DECREMENTED = 1
}	t_parenthesis;

typedef struct s_quotes_part
{
	t_strpart_type			type;
	char					*part;
	struct s_quotes_part	*next;
	t_bool					shifted_due_to_env_lex_expand;
	t_bool					built_expanded_into_latest_strpart;
}	t_quotes_part;

typedef struct s_env
{
	char			*key;
	char			*value;
	char			*string;
	struct s_env	*next;
}	t_env;

typedef struct s_lexer
{
	char			*word;
	t_token_type	token_type;
	struct s_lexer	*next;
	t_bool			dynamic_joining;
	t_bool			extra_space_if_new_strpart;
}	t_lexer;

typedef struct s_command
{
	t_lexer				*arg_lst;
	t_lexer				*in_lst;
	t_lexer				*out_lst;
	struct s_command	*next;
	t_builtin			builtin;
	t_token_type		operator;
	int					cmd_group_len;
	int					parenthesis_cnt_personal;
	int					parenthesis_status;
}	t_cmd;

typedef struct s_buffer
{
	t_env				*env_list;
	t_env				*backup_env_list;
	t_lexer				*lexer_list;
	t_cmd				*cmd_list;
	int					std_in;
	int					std_out;
	int					pipefd_in;
	int					exit_status;
	int					exit_status_saved;
	char				*err_msg;
	t_lexer				**lex_ptrs;
	t_cmd				**group_start_cmd;
	int					cmd_group_logic_status;
	int					cmd_group_temp_cnt;
	int					group_cmds_i;
	char				**envp;
	int					is_pipe;
	int					is_child;
	char				*input_line;
	struct sigaction	ctrl_c;
	struct sigaction	ctrl_back_slash;
}	t_buffer;

// cleaner.c
void	print_error(int code, char *err_msg);
void	clean_and_exit(t_exit_code code, t_buffer *buffer);

// signals.c
void	define_signals(t_buffer *buffer, t_sig_mode mode);

// builtins/b_cd.c
void	b_cd(t_buffer *buffer, t_lexer *arg_lst);

// builtins/b_export.c
void	b_export(t_buffer *buffer, t_lexer *arg_lst);

// builtins/builtins_others.c
void	b_echo(t_buffer *buffer, t_lexer *arg_lst);
void	b_env(t_buffer *buffer, t_lexer *arg_lst);
void	b_exit(t_buffer *buffer, t_lexer *arg_lst);
void	b_pwd(t_buffer *buffer, t_lexer *arg_lst);
void	b_unset(t_buffer *buffer, t_lexer *arg_lst);

// builtins/builtins_utils.c
int		atoi_exit_code(const char *str);
void	b_cd_error(t_buffer *buffer);
void	b_exit_error(t_buffer *buffer, char *arg_str);
t_bool	is_n_option(char *str);

// environment/env_create_and_change.c
t_env	*add_new_env(t_buffer *buffer, char *key, char *value, char *env_str);
t_env	*create_env(t_buffer *buffer, char *key, char *value);
void	set_env_value_dup(t_env	*env, char *value, t_buffer *buffer);
int		set_env(t_buffer *buffer, char *key, char *value, char *env_str);

// environment/env_delete_and_free.c
void	free_env_list(t_buffer *buffer);
void	free_env_value(t_env *env);
t_bool	delete_env(t_buffer *buffer, char *key);

// environment/env_get.c
t_env	*get_env(t_env *env_lst, char *key);
char	*get_env_value(t_env *env_lst, char *key, char *default_str);
int		get_envp_index(char **envp, char *str);
int		get_key_value(char *env_str, char **key, char **value);
char	*get_home_path(t_buffer *buffer);

// environment/init_environment.c
void	clone_environment(char *envp[], t_buffer *buffer);
void	get_envp_array(t_buffer *buffer);

// environment/shlvl.c
void	env_shlvl_init(t_buffer *buffer);
void	env_shlvl_set(t_buffer *buffer, char *new_value);
void	env_shlvl_export(t_buffer *buffer, char *str);

// executor/command_execute.c
pid_t	exec_command(t_lexer *lexer_arg, t_cmd *cmd, t_buffer *buffer);

// executor/command_prepare.c
char	*get_cmd(char *cmd, t_buffer *buffer);
char	**get_args_array(t_lexer *lexer);
void	cmd_malloc_error_check(t_buffer *buffer, char *cmd, char **cmd_args);

// executor/executor_main.c
void	executor(t_buffer *buffer);

// executor/executor_utils.c
void	replace_std_fd(int fd, int std_fd, t_buffer *buffer);
t_bool	get_last_child_status(pid_t pid, t_buffer *buffer);
t_bool	is_cmd_in_pipe(t_cmd *cmd);
void	free_array(char **array);
char	*get_temp_filename(int i, t_buffer *buffer);

// executor/heredoc.c
void	resolve_heredocs(t_buffer *buffer);

// executor/input_output.c
void	set_input(t_lexer *lexer_in, t_buffer *buffer);
void	set_output(t_lexer *lexer_out, t_buffer *buffer, int fd_out);

// Rik's functions
char	*join_strparts(t_quotes_part *str_part_lst,
			t_buffer *buffer, int *wild_card_quotes_check);
int		strpart_strlen(t_quotes_part *cur_str_part, int except_last);
int		try_noquotes_str(char *line, int *i,
			t_quotes_part **str_part_lst, t_buffer *buffer);
int		try_quotes_str(char *line, int *i,
			t_quotes_part **str_part_lst, t_buffer *buffer);
void	expand_str(char	**target_to_expand_ptr, char *str2, t_buffer *buffer);

t_lexer	**save_lex_ptrs(t_lexer *lexer, t_buffer *buffer);
t_lexer	*lex_lstnew(char *word, int token, t_buffer *buffer);
void	lex_lstadd_back(t_lexer **lst, t_lexer *new);
t_lexer	*lex_lstlast(t_lexer *lst);
void	join_strparts_normally(t_quotes_part *str_part_lst, t_buffer *buffer);

int		check_group_cnts(t_buffer *buffer, t_lexer **lex_cur);

#endif
