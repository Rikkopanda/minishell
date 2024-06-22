/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:02:28 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/25 19:27:30 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

typedef struct s_lexer		t_lexer;
typedef struct s_command	t_cmd;
typedef struct s_buffer		t_buffer;
typedef void				(*t_builtin)(t_buffer*, t_lexer*);

// try tokens in parser
void		parser(t_cmd **command_lst, t_lexer	*lex_cur, t_buffer *buffer);
int			try_parenthesis(
				t_lexer	**lex_cur, t_buffer *buffer);
int			try_pipe_or_logic_token(t_cmd	**cmd_cur,
				t_lexer	**lex_cur, t_buffer *buffer);

// parser helpers
t_builtin	find_builtin(t_lexer *try_arg);
int			move_in_out_nodes2(t_lexer **redir_lst,
				t_lexer **lex_cur, t_buffer *buffer);

// parenthesis logic
int			check_if_operator(t_lexer **lex_cur);

int			check_parenthesis_after_word(
				t_lexer	**lex_cur);
int			try_beginning_group(
				t_lexer	**lex_cur, t_buffer *buffer);
int			try_ending_group(
				t_lexer	**lex_cur, t_buffer *buffer);
int			decrement_all_cmd_cnts(t_buffer *buffer);
void		increment_all_open_groups_cnt(t_buffer *buffer);
void		increase_lenght_previous_groups(t_buffer *buffer);
void		update_cmd_array(t_buffer *buffer, t_cmd *cmd_cur);
void		try_add_cmd_to_ptr_array(t_cmd *cmd_cur, t_buffer *buffer);
int			check_group_cnts(t_buffer *buffer, t_lexer **lex_cur);
int			t_cmd_ptrs_len(t_cmd **ptr_arr);
void		init_cmd_group_logic(t_buffer *buffer);
void		init_cmd_array(int len, t_buffer *buffer);

// debug
int			print_cmd_group_array(t_buffer *buffer);

#endif