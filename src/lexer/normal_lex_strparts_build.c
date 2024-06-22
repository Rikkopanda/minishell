/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_lex_strparts_build.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:27:48 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/25 19:26:15 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	build_lexes(int wild_card_quotes_check, char *new_str,
	char *total_str, t_buffer *buffer)
{
	if (wild_card_quotes_check)
		lex_lstadd_back(&buffer->lexer_list,
			lex_lstnew(new_str, WORD, buffer));
	else if (scan_and_try_wildcard(total_str, buffer, FALSE) == MATCHING)
		free(new_str);
	else
		lex_lstadd_back(&buffer->lexer_list,
			lex_lstnew(new_str, WORD, buffer));
}

/**
 * normally apposed to during the while loop
 * when a lex/ new lex is expanded from env
*/
void	join_strparts_normally(t_quotes_part	*str_part_lst, t_buffer *buffer)
{
	char	*total_str;
	int		wild_card_quotes_check;
	char	*new_str;

	wild_card_quotes_check = 0;
	total_str = join_strparts(str_part_lst, buffer,
			&wild_card_quotes_check);
	if (!total_str)
		return ;
	if (total_str[0] == '\0')
	{
		free(total_str);
		return ;
	}
	new_str = ft_strdup(total_str);
	if (!new_str)
		clean_and_exit(MALLOC_ERROR, buffer);
	build_lexes(wild_card_quotes_check, new_str, total_str, buffer);
	free(total_str);
}

void	post_joining_and_clearing_parts(int *start, int	*i,
	t_quotes_part	*str_part_lst, t_buffer *buffer)
{
	if (*i > *start && check_last_lex_node_if_came_from_env(buffer) == FALSE)
		join_strparts_normally(str_part_lst, buffer);
	if (buffer->lexer_list != NULL)
		lex_lstlast(buffer->lexer_list)->dynamic_joining = FALSE;
	clear_part_lst(str_part_lst);
}
