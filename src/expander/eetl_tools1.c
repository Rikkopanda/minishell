/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eetl_tools1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:15:25 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/22 21:33:49 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	put_pointers_in_holder_1(t_parameter_pts_holder *p,
	t_insert_expand_tools *tools,
	t_quotes_part **str_part_lst, t_buffer *buffer)
{
	p->tools = tools;
	p->str_part_lst = str_part_lst;
	p->buffer = buffer;
}

void	put_pointers_in_holder_2(t_parameter_pts_holder	*p,
	t_insert_expand_tools *eetl_tools,
	t_quotes_part *latest_part, char *expanded_str)
{
	p->eetl_tools = eetl_tools;
	p->latest_part = latest_part;
	p->expanded_str = expanded_str;
}

void	reset_eetl_conditions(t_insert_expand_tools *eetl_tools)
{
	eetl_tools->space_preceding_first_lex = FALSE;
	eetl_tools->space_after_last_lex = FALSE;
}

/**
 * between lexers and after the last one
*/
int	parse_between_and_after_spaces(char	*expanded_str,
	t_insert_expand_tools *eetl_tools)
{
	while (expanded_str[eetl_tools->i] == ' '
		|| expanded_str[eetl_tools->i] == '\t')
	{
		eetl_tools->i += SKIP_SPACE_CHAR;
	}
	if (expanded_str[eetl_tools->i] == '\0')
		return (END);
	else
		return (SUCCESS);
}

void	eetl_parse_word(char *expanded_str,
	t_insert_expand_tools *eetl_tools)
{
	while (expanded_str[eetl_tools->i] != ' '
		&& expanded_str[eetl_tools->i] != '\t'
		&& expanded_str[eetl_tools->i] != '\0')
		eetl_tools->i++;
}
