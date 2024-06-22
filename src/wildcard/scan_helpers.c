/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:16:06 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/26 11:42:49 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	scan_post_asterix(int *i, t_quotes_part *ls_current,
	t_asterix_pattern *pattern_node)
{
	int	j;

	j = 0;
	if (!pattern_node)
		return (MATCHING);
	if (pattern_node->last_post_asterix != NULL)
	{
		while (ls_current->part[*i] == pattern_node->last_post_asterix[j]
			&& ls_current->part[*i] != '\0')
		{
			(*i)++;
			j++;
		}
		if (pattern_node->last_post_asterix[j] == '\0'
			&& ls_current->part[*i] == '\0')
			return (MATCHING);
		return (NOT_MATCHING);
	}
	return (MATCHING);
}
// printf("post: %s\n", pattern_node->last_post_asterix);

int	scan_first_pre_case(int	*i, t_quotes_part *ls_current,
	t_asterix_pattern *pattern_node)
{
	int	j;

	j = 0;
	if (pattern_node == NULL)
		return (MATCHING);
	if (pattern_node->pre_asterix != NULL)
	{
		while (ls_current->part[*i] == pattern_node->pre_asterix[j]
			&& ls_current->part[*i] != '\0')
		{
			(*i)++;
			j++;
		}
		if (pattern_node->pre_asterix[j] != '\0')
			return (NOT_MATCHING);
		else
			return (MATCHING);
	}
	return (MATCHING);
}

int	scan_pre_asterix(int	*i, t_quotes_part *ls_current,
	t_asterix_pattern *pattern_node)
{
	int	j;

	j = 0;
	if (pattern_node == NULL)
		return (MATCHING);
	if (pattern_node->pre_asterix != NULL)
	{
		while (ls_current->part[*i] != pattern_node->pre_asterix[0]
			&& ls_current->part[*i] != '\0')
			(*i)++;
		while (ls_current->part[*i] == pattern_node->pre_asterix[j]
			&& ls_current->part[*i] != '\0')
		{
			(*i)++;
			j++;
		}
		if (pattern_node->pre_asterix[j] == '\0')
			return (MATCHING);
		return (NOT_MATCHING);
	}
	return (MATCHING);
}
// printf("ls_cur %s\n", ls_current->part);
// printf("pattern %s\n", pattern_node->pre_asterix);

int	check_post_asterix(t_quotes_part *current_ls_node,
	t_asterix_pattern *pattern_node, int *i)
{
	if (pattern_node->last_post_asterix == NULL)
		return (MATCHING);
	while (current_ls_node->part[*i] != '\0')
	{
		if (current_ls_node->part[*i] != pattern_node->last_post_asterix[0]
			&& current_ls_node->part[*i] != '\0')
			(*i)++;
		if (scan_post_asterix(i, current_ls_node, pattern_node) == MATCHING)
			return (MATCHING);
	}
	return (NOT_MATCHING);
}
// printf("failcase : %s %d\n\n", &current_ls_node->part[*i], *i);
// printf("post : %s %d\n", &current_ls_node->part[*i], *i);