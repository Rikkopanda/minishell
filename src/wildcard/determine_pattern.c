/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determine_pattern.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:53:47 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/25 19:27:54 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

t_asterix_pattern	*pattern_node_new(void)
{
	t_asterix_pattern	*new_node;

	new_node = malloc(sizeof(t_asterix_pattern));
	new_node->pre_asterix = NULL;
	new_node->last_post_asterix = NULL;
	new_node->next = NULL;
	new_node->type = 0;
	return (new_node);
}

int	try_first_node(char *wildcard_str,
	t_asterix_pattern **first_node, t_buffer *buffer, int *i)
{
	int	len;

	if (wildcard_str[*i] == '\'')
		return ((*first_node)->type = ABSOLUTE_DIRECTORY_PATTERN, ERROR);
	if (wildcard_str[*i] == '.')
		(*first_node)->type = HIDDEN_FILES;
	while (wildcard_str[*i] != '*'
		&& wildcard_str[*i] != '\0' && wildcard_str[*i] != '\'')
		(*i)++;
	if (wildcard_str[*i] == '\'')
		return (ERROR);
	len = *i - 0;
	if (len == 0)
		(*first_node)->pre_asterix = NULL;
	else
	{
		(*first_node)->pre_asterix = ft_substr(wildcard_str, 0, len);
		if (!(*first_node)->pre_asterix)
			clean_and_exit(MALLOC_ERROR, buffer);
	}
	return (SUCCESS);
}

void	wildcard_str_parse_loop(char *wildcard_str, t_index_tools *tools,
	t_asterix_pattern **current_node, t_buffer *buffer)
{
	(*current_node)->next = pattern_node_new();
	(*current_node) = (*current_node)->next;
	build_pre_asterix_part(wildcard_str, *current_node, buffer, tools);
	while (wildcard_str[*tools->i_ptr] == '*')
		(*tools->i_ptr)++;
	tools->start = *tools->i_ptr;
	while (wildcard_str[*tools->i_ptr] != '*'
		&& wildcard_str[*tools->i_ptr] != '\0'
		&& wildcard_str[*tools->i_ptr] != '\'')
		(*tools->i_ptr)++;
	if (wildcard_str[*tools->i_ptr] == '\0')
		build_last_post_asterix_part(wildcard_str,
			*current_node, buffer, tools);
}

int	try_next_nodes(char *wildcard_str,
	t_asterix_pattern **current_node, t_buffer *buffer, int *i)
{
	t_index_tools	tools;

	init_part_build_tools(&tools, i);
	while (wildcard_str[*i] != '*'
		&& wildcard_str[*i] != '\0' && wildcard_str[*i] != '\'')
		(*i)++;
	if (wildcard_str[*i] == '\'')
		return (ERROR);
	if (wildcard_str[*i] == '\0')
		return (only_one_node(wildcard_str, current_node, buffer, &tools));
	while (wildcard_str[*i] != '\0')
		wildcard_str_parse_loop(wildcard_str, &tools, current_node, buffer);
	return (SUCCESS);
}

int	determine_current_pattern(char *wildcard_str,
	t_asterix_pattern **pattern_lst, t_buffer *buffer)
{
	int					j;
	t_asterix_pattern	*first_node;
	t_asterix_pattern	*current_node;

	*pattern_lst = pattern_node_new();
	first_node = *pattern_lst;
	j = 0;
	if (try_first_node(wildcard_str, &first_node, buffer, &j) == ERROR)
		return (ERROR);
	while (wildcard_str[j] == '*')
		j++;
	current_node = first_node;
	if (try_next_nodes(wildcard_str, &current_node, buffer, &j) == ERROR)
		return (ERROR);
	return (ONLY_CURRENT_DIRECTORY_PATTERN);
}
