/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:38:41 by rverhoev          #+#    #+#             */
/*   Updated: 2024/04/25 19:28:12 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

t_wildcard_code	expand_wildcard(char *wildcard_str, t_buffer *buffer,
	t_bool str_is_from_a_lex)
{
	t_asterix_pattern	*pattern;
	t_quotes_part		*content_list;

	content_list = NULL;
	pattern = NULL;
	if (determine_current_pattern(wildcard_str, &pattern, buffer)
		!= ONLY_CURRENT_DIRECTORY_PATTERN)
		return (NOT_MATCHING);
	read_current_directory_into_list(&content_list, buffer, pattern);
	if (store_matching_list_in_str(pattern, &content_list, buffer,
			str_is_from_a_lex) == MATCHING)
		return (clean_up_wildcard(pattern, &content_list), MATCHING);
	else
		return (clean_up_wildcard(pattern, &content_list), NOT_MATCHING);
}
// printf("\nnew expanded: %s\n\n", latest_part->part);
// if (pattern.match_pre_asterix != NULL)
// 	printf("%s\n", pattern.match_pre_asterix);
// if (pattern.match_pre_asterix != NULL)
// 	printf("%s\n", pattern.match_post_asterix);

int	scan_and_try_wildcard(char *total_expanded_str,
	t_buffer *buffer, t_bool str_is_from_a_lex)
{
	int	i;
	int	asterix_found;

	if (total_expanded_str == NULL)
		return (NOT_MATCHING);
	i = 0;
	asterix_found = 0;
	while (total_expanded_str[i] != '\0')
	{
		if (total_expanded_str[i] == '*')
			asterix_found = 1;
		i++;
	}
	if (asterix_found)
		return (expand_wildcard(total_expanded_str,
				buffer, str_is_from_a_lex));
	else
		return (NOT_MATCHING);
}
