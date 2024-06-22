/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:49:56 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/28 09:59:11 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# define EXTRA_SIZE_FOR_SPACE 1
# define EXTRA_SIZE_FOR_TERMINATOR 1
# define SKIP_SPACE_CHAR 1
# define TRIM_EXPANDED_SINGLE_WORD -1
# define NO_ENV_EXPAND 0
# include "../minishell.h"

typedef struct s_lexer			t_lexer;
typedef struct s_command		t_cmd;
typedef struct s_buffer			t_buffer;
typedef struct s_quotes_part	t_quotes_part;
typedef enum e_expand_code		t_expand_code;
typedef enum e_bool				t_bool;

typedef enum e_expand_parse_code
{
	DONT_EXPAND_ALL,
	DONT_EXPAND_ENV,
	DO_EXPAND
}	t_expand_parse_code;

typedef struct s_insert_expand_tools
{
	int		len;
	int		start;
	int		i;
	int		eetl_build_lex_i;
	int		space_preceding_first_lex;
	int		space_after_last_lex;
	int		cutoff_next_env_part_i;
}	t_insert_expand_tools;

typedef struct s_parameter_pts_holder
{
	t_buffer				*buffer;
	t_quotes_part			**str_part_lst;
	t_quotes_part			*latest_part;
	t_insert_expand_tools	*eetl_tools;
	t_insert_expand_tools	*tools;
	char					*expanded_str;
	char					*expanded_substr;
	char					*original_pre_env;
	char					*original_whole_str;
	char					*remaining_new_env;
}	t_parameter_pts_holder;

void	expand_home(t_parameter_pts_holder *p,
			t_quotes_part *latest_part);
int		build_expanded_part(t_parameter_pts_holder *p,
			t_quotes_part *latest_part, char *line_point);
void	building_errno_case(t_parameter_pts_holder *p,
			t_quotes_part *latest_part);
void	handle_remaining_str_last(t_insert_expand_tools	*tools,
			t_parameter_pts_holder *p,
			t_quotes_part **str_part_lst, t_buffer *buffer);
int		check_char_after_dollar(char chr);
void	insert_expanded_str_into_latest_part(char *expanded_str,
			t_quotes_part *latest_part,
			t_insert_expand_tools *tools, t_buffer *buffer);
int		if_dollar_is_last_and_no_following_strparts(
			char *checking_strpart_point, char *line_point);
void	try_expander(t_quotes_part **str_part_lst,
			t_buffer *buffer, char *line_point);

// helper functions
void	init_index_tools(t_insert_expand_tools	*tools);
void	expand_errno_case(char **expanded_str,
			t_insert_expand_tools *tools, t_buffer *buffer);
int		special_char_list(char check_char);
int		check_if_strpart_will_expand(t_quotes_part *str_part_lst,
			char *line_point);
int		env_expand_check(t_insert_expand_tools	*tools,
			t_quotes_part *latest_part, char *line_point);
void	put_pointers_in_holder_1(t_parameter_pts_holder	*p,
			t_insert_expand_tools *tools,
			t_quotes_part	**str_part_lst, t_buffer *buffer);
void	put_pointers_in_holder_2(t_parameter_pts_holder	*p,
			t_insert_expand_tools *eetl_tools,
			t_quotes_part	*latest_part, char *expanded_str);
char	*join_strparts_except_last(t_quotes_part *str_part_lst,
			t_buffer *buffer);
void	empty_and_reset_parts(t_quotes_part *cur_part);
void	cutoff_and_move_new_env(t_parameter_pts_holder *p,
			t_quotes_part *latest_part);
void	build_empty_str(char **expanded_str, t_buffer *buffer);
int		check_if_dollar_adjecent_to_new_quotes(char *checking_strpart_point,
			char *line_point);
// env expand to lexes -- eetl
int		try_env_expand_to_lex_nodes(t_parameter_pts_holder *p,
			t_quotes_part *latest_part);
// build first expanded lexes
void	build_first_expanded_lex(t_parameter_pts_holder *p,
			char *expanded_substr);
void	preceding_space_case_build_lex(t_parameter_pts_holder *p,
			char *expanded_substr);
void	joining_strpart_to_env_expanded_lex(t_parameter_pts_holder *p,
			t_buffer *buffer);
void	build_case_no_parts_to_join(t_parameter_pts_holder *p,
			int wild_card_quotes_check);
void	build_case_glue_to_last_lex(t_parameter_pts_holder *p,
			char *total_str_2);
void	build_preceding_strpart_into_lex(t_parameter_pts_holder *p);
void	build_new_lex(t_parameter_pts_holder *p,
			int *wild_card_quotes_check, char *totalstr);
int		join_previous_parts_to_str(t_parameter_pts_holder *p,
			char	**totalstr, int *wild_card_quotes_check);
//
void	reset_eetl_conditions(t_insert_expand_tools *eetl_tools);
int		parse_between_and_after_spaces(char	*expanded_str,
			t_insert_expand_tools	*eetl_tools);
void	eetl_parse_word(char	*expanded_str,
			t_insert_expand_tools	*eetl_tools);
void	trim_str(int j, char *str);
int		check_for_multiple_words_or_spaces(char	*expanded_str);
void	parse_preceding_spaces(char	*expanded_str,
			t_insert_expand_tools	*eetl_tools);
int		check_if_last_expansion(char *expand_str_point);

#endif