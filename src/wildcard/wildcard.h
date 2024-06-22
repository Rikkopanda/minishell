/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:50:56 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/25 19:28:58 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "../minishell.h"

typedef struct s_asterix_pattern	t_asterix_pattern;
typedef enum e_bool					t_bool;

struct s_asterix_pattern
{
	char				*pre_asterix;
	char				*last_post_asterix;
	t_asterix_pattern	*next;
	int					type;
};

typedef enum e_wildcard_code
{
	NOT_MATCHING,
	MATCHING,
	ONLY_CURRENT_DIRECTORY_PATTERN,
	MULTI_DIRECTORY_PATTERN,
	ABSOLUTE_DIRECTORY_PATTERN,
	HIDDEN_FILES
}	t_wildcard_code;

typedef struct s_read_dir_ptrs
{
	char				*current_dir_of_process;
	DIR					*dir_stream;
	struct dirent		*dir_data;
	t_asterix_pattern	*pattern;
	t_quotes_part		**content_list;
	t_buffer			*buffer;
}	t_read_dir_ptrs;

typedef struct s_index_tools
{
	int	start;
	int	*i_ptr;
	int	j;
	int	len;
}	t_index_tools;

int		scan_and_try_wildcard(char *total_expanded_str,
			t_buffer *buffer, t_bool str_is_from_a_lex);
// determine pattern
int		determine_current_pattern(char *wildcard_str,
			t_asterix_pattern **pattern_lst,
			t_buffer *buffer);
int		try_first_node(char *wildcard_str,
			t_asterix_pattern **first_node, t_buffer *buffer, int *i);
int		try_next_nodes(char *wildcard_str,
			t_asterix_pattern **current_node, t_buffer *buffer, int *i);

// pattern build functions
int		only_one_node(char *wildcard_str, t_asterix_pattern **first_node,
			t_buffer *buffer, t_index_tools *tools);
void	build_pre_asterix_part(char *wildcard_str, t_asterix_pattern *node,
			t_buffer *buffer, t_index_tools *tools);
int		build_last_post_asterix_part(char *wildcard_str,
			t_asterix_pattern *node, t_buffer *buffer, t_index_tools *tools);

// read directory into list
void	read_current_directory_into_list(t_quotes_part **content_list,
			t_buffer *buffer, t_asterix_pattern	*pattern);
void	sort_linked_list_alphabetical(t_quotes_part **content_list,
			int i, int j, const int size);

// scan and store matching nodes
int		store_matching_list_in_str(t_asterix_pattern *pattern_node,
			t_quotes_part **content_list,
			t_buffer *buffer, t_bool str_is_from_a_lex);
int		scan_post_asterix(int *i, t_quotes_part *ls_current,
			t_asterix_pattern *pattern_node);
int		scan_first_pre_case(int	*i, t_quotes_part *ls_current,
			t_asterix_pattern *pattern_node);
int		scan_pre_asterix(int	*i, t_quotes_part *ls_current,
			t_asterix_pattern *pattern_node);
int		check_post_asterix(t_quotes_part *current_ls_node,
			t_asterix_pattern *pattern_node, int *i);

// helpers
int		check_for_hidden_content(char *name);
void	init_part_build_tools(t_index_tools *tools, int *i);
int		linked_list_size(t_quotes_part *node);

// cleanup
void	clean_up_dir_content(t_quotes_part **content_list);
void	clean_up_pattern(t_asterix_pattern *pattern_node);
void	clean_up_wildcard(t_asterix_pattern *pattern,
			t_quotes_part **content_list);

#endif