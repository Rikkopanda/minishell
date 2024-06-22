/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:30:23 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/24 13:31:36 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * if last lex expanded from env
*/
int	check_last_lex_node_if_came_from_env(t_buffer *buffer)
{
	if (buffer->lexer_list != NULL)
	{
		if (lex_lstlast(buffer->lexer_list)->dynamic_joining == TRUE)
			return (TRUE);
		else
			return (FALSE);
	}
	return (FALSE);
}

/**
 * after a env lexes expansion, the strpart_str was shifted
 * with remaining str a new strpart is made
 * this is eventually still expanded in expander(insertion)
 * and eventually this has to be added to last lex
*/
int	last_strpart_shifted_for_env_expanded(t_quotes_part	*str_part_lst)
{
	if (str_part_lst != NULL)
	{
		if (strpart_lstlast(str_part_lst)
			->shifted_due_to_env_lex_expand == TRUE)
			return (TRUE);
		else
			return (FALSE);
	}
	return (FALSE);
}
