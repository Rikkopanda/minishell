/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:16:44 by rverhoev          #+#    #+#             */
/*   Updated: 2024/04/25 19:26:06 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../minishell.h"

typedef struct s_lexer			t_lexer;
typedef struct s_command		t_cmd;
typedef struct s_buffer			t_buffer;
typedef struct s_quotes_part	t_quotes_part;

typedef struct s_try_quotes_tools
{
	int		begin_quote;
	int		start;
	int		len;
	int		*i_ptr;
	char	*line;
	char	*new_str;
}	t_try_quotes_tools;

typedef struct s_joining_vars
{
	t_lexer	*last_lex;
	int		wild_card_quotes_check;
	char	*joined_strparts;
	char	*tmp_str;
}	t_joining_vars;

int		lexer(char *line, t_buffer *buffer);
void	try_tokens(char *line, int	*i, t_buffer *buffer);
void	try_word(int *start, char *line, int	*i, t_buffer *buffer);
int		try_quotes_str(char *line, int	*i,
			t_quotes_part	**str_part_lst, t_buffer *buffer);
int		try_noquotes_str(char *line, int *i,
			t_quotes_part **str_part_lst, t_buffer *buffer);
void	clear_part_lst(t_quotes_part *str_part_lst);

// lex_lst std functions
t_lexer	**save_lex_ptrs(t_lexer *lexer, t_buffer *buffer);
t_lexer	*lex_lstnew(char *word, int token, t_buffer *buffer);
void	lex_lstadd_back(t_lexer **lst, t_lexer *new);
t_lexer	*lex_lstlast(t_lexer *lst);

// env expansion helpers
int		check_last_lex_node_if_came_from_env(t_buffer *buffer);
int		last_strpart_shifted_for_env_expanded(t_quotes_part	*str_part_lst);

// joining
void	join_strparts_normally(t_quotes_part	*str_part_lst,
			t_buffer *buffer);
int		scan_strparts_quotes_for_wildcard_check(t_quotes_part *str_part_lst);
void	join_latest_str_part_to_last_lex(t_quotes_part *str_part_lst,
			t_buffer *buffer);
void	post_joining_and_clearing_parts(int *start, int	*i,
			t_quotes_part *str_part_lst, t_buffer *buffer);
void	normal_new_node_lex(char *joined_strparts,
			t_buffer *buffer);
int		fresh_lex_node_build(char *joined_strparts,
			t_buffer *buffer, int wild_card_quotes_check);
void	glue_str_to_part(t_lexer *last_lex, char *joined_strparts,
			t_buffer *buffer, int wild_card_quotes_check);
// helpers
int		check_non_printable(char *line);
void	scan_part_on_wildcard_quote_check(t_quotes_part	*cur_str_part,
			int *wild_card_quotes_check);
void	init_try_quotes_tools(t_try_quotes_tools *tools,
			char *line, int i, int *i_ptr);
int		check_to_continue(char *line, int	*i);
int		check_dynamic_join_last_part(t_quotes_part	*str_part_lst,
			char *line, int	*i, t_buffer *buffer);
int		check_dynamic_join_post_expansion(t_quotes_part	*str_part_lst,
			t_buffer *buffer);

#endif
