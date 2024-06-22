/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_cleaner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:52:27 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/21 15:14:07 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	clean_up_dir_content(t_quotes_part **content_list)
{
	t_quotes_part	*current_node;
	t_quotes_part	*tmp_node;

	current_node = *content_list;
	while (current_node != NULL)
	{
		tmp_node = current_node;
		current_node = current_node->next;
		free(tmp_node->part);
		free(tmp_node);
	}
}

void	clean_up_pattern(t_asterix_pattern *pattern_node)
{
	t_asterix_pattern	*tmp;

	while (pattern_node != NULL)
	{
		if (pattern_node->pre_asterix != NULL)
			free(pattern_node->pre_asterix);
		if (pattern_node->last_post_asterix != NULL)
			free(pattern_node->last_post_asterix);
		tmp = pattern_node->next;
		free(pattern_node);
		pattern_node = tmp;
	}
}

void	clean_up_wildcard(t_asterix_pattern *pattern,
	t_quotes_part **content_list)
{
	clean_up_dir_content(content_list);
	clean_up_pattern(pattern);
}
