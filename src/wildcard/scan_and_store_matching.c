/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_and_store_matching.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:05:32 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/25 16:19:42 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

t_wildcard_code	check_for_matching(t_quotes_part *current_ls_node,
	t_asterix_pattern *pattern_node)
{
	int	i;

	i = 0;
	if (scan_first_pre_case(&i, current_ls_node, pattern_node) != MATCHING)
		return (NOT_MATCHING);
	while (pattern_node->next != NULL)
	{
		pattern_node = pattern_node->next;
		if (pattern_node == NULL)
			break ;
		if (scan_pre_asterix(&i, current_ls_node, pattern_node) != MATCHING)
			return (NOT_MATCHING);
	}
	if (pattern_node == NULL)
		return (MATCHING);
	if (check_post_asterix(current_ls_node, pattern_node, &i) == MATCHING)
		return (MATCHING);
	else
		return (NOT_MATCHING);
}
// if (pattern_node)
// 	printf("%s\t", pattern_node->pre_asterix);

void	add_matching(t_quotes_part *current_ls_node,
	int i, t_bool str_is_from_a_lex, t_buffer *buffer)
{
	char	*new_str;

	new_str = ft_strdup(current_ls_node->part);
	if (!new_str)
		clean_and_exit(MALLOC_ERROR, buffer);
	if (i == 0 && str_is_from_a_lex == TRUE)
	{
		lex_lstlast(buffer->lexer_list)->word = new_str;
		if (lex_lstlast(buffer->lexer_list)->word == NULL)
			clean_and_exit(MALLOC_ERROR, buffer);
	}
	else
		lex_lstadd_back(&buffer->lexer_list,
			lex_lstnew(new_str, WORD, buffer));
}

/**
 * in case str came from the latest lex(not a strpart_node
 * , that lex's word must be replaced 
 * the the resulting match str(from ls_node). Only the first ls_node
*/
int	store_matching_list_in_str(t_asterix_pattern *pattern_node,
	t_quotes_part **content_list, t_buffer *buffer, t_bool str_is_from_a_lex)
{
	t_quotes_part	*current_ls_node;
	t_wildcard_code	matching_status;
	int				i;

	i = 0;
	matching_status = NOT_MATCHING;
	current_ls_node = *content_list;
	while (current_ls_node != NULL)
	{
		if (check_for_matching(current_ls_node, pattern_node) != MATCHING)
			current_ls_node = current_ls_node->next;
		else
		{
			add_matching(current_ls_node, i, str_is_from_a_lex, buffer);
			matching_status = MATCHING;
			i++;
			current_ls_node = current_ls_node->next;
		}
	}
	return (matching_status);
}
