/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_part_joining_helpers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:00:51 by rverhoev          #+#    #+#             */
/*   Updated: 2024/04/25 19:01:06 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	normal_new_node_lex(char *joined_strparts,
	t_buffer *buffer)
{
	char	*new_str;

	new_str = ft_strdup(joined_strparts);
	if (!new_str)
		clean_and_exit(MALLOC_ERROR, buffer);
	lex_lstadd_back(&buffer->lexer_list,
		lex_lstnew(new_str, WORD, buffer));
}

int	fresh_lex_node_build(char *joined_strparts,
	t_buffer *buffer, int wild_card_quotes_check)
{
	if (joined_strparts[0] == '\0')
	{
		free(joined_strparts);
		return (NONE);
	}
	else if (wild_card_quotes_check == TRUE)
	{
		normal_new_node_lex(joined_strparts, buffer);
	}
	else if (scan_and_try_wildcard(joined_strparts,
			buffer, FALSE) != MATCHING)
	{
		normal_new_node_lex(joined_strparts, buffer);
	}
	return (SUCCESS);
}

void	glue_str_to_part(t_lexer *last_lex, char *joined_strparts,
	t_buffer *buffer, int wild_card_quotes_check)
{
	expand_str(&last_lex->word,
		joined_strparts, buffer);
	if (wild_card_quotes_check == TRUE)
		scan_and_try_wildcard(last_lex->word, buffer, TRUE);
}
