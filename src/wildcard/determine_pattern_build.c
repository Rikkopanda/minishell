/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determine_pattern_build.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:58:57 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/21 16:25:29 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	only_one_node(char *wildcard_str, t_asterix_pattern **first_node,
	t_buffer *buffer, t_index_tools *tools)
{
	int	len;

	len = *tools->i_ptr - tools->start;
	if (len == 0)
		(*first_node)->last_post_asterix = NULL;
	else
	{
		(*first_node)->last_post_asterix = ft_substr(wildcard_str,
				tools->start, len);
		if (!(*first_node)->last_post_asterix)
			clean_and_exit(MALLOC_ERROR, buffer);
	}
	return (SUCCESS);
}

// int	only_one_node(char *wildcard_str, t_asterix_pattern
//		**first_node, t_buffer *buffer, int start, int *i)
// {
// 	return (add_to_first_node(wildcard_str, first_node, buffer, start, i));
// }

void	build_pre_asterix_part(char *wildcard_str, t_asterix_pattern *node,
	t_buffer *buffer, t_index_tools *tools)
{
	int	len;

	len = *tools->i_ptr - tools->start;
	if (len == 0)
		node->pre_asterix = NULL;
	else
	{
		node->pre_asterix = ft_substr(wildcard_str, tools->start, len);
		if (!node->pre_asterix)
			clean_and_exit(MALLOC_ERROR, buffer);
	}
}

int	build_last_post_asterix_part(char *wildcard_str, t_asterix_pattern *node,
	t_buffer *buffer, t_index_tools *tools)
{
	int	len;

	len = *tools->i_ptr - tools->start;
	if (len == 0)
		node->last_post_asterix = NULL;
	else
	{
		node->last_post_asterix = ft_substr(wildcard_str, tools->start, len);
		if (!node->last_post_asterix)
			clean_and_exit(MALLOC_ERROR, buffer);
	}
	return (SUCCESS);
}
