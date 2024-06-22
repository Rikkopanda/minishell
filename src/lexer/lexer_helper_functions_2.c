/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper_functions_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:25:48 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/29 10:20:01 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	strpart_strlen(t_quotes_part *cur_str_part, int except_last)
{
	int	str_len;

	str_len = 0;
	while (cur_str_part != NULL)
	{
		if (cur_str_part->next == NULL && except_last)
			return (str_len + SPACE_FOR_NULL_TERM);
		str_len += ft_strlen(cur_str_part->part);
		cur_str_part = cur_str_part->next;
	}
	return (str_len + SPACE_FOR_NULL_TERM);
}

void	scan_part_on_wildcard_quote_check(t_quotes_part	*cur_str_part,
	int *wild_card_quotes_check)
{
	int	i;

	i = 0;
	while (cur_str_part->part[i] != '\0')
	{
		if (cur_str_part->part[i] == '*'
			&& (cur_str_part->type == SINGLE_QUOTE
				|| cur_str_part->type == DOUBLE_QUOTE))
			*wild_card_quotes_check = 1;
		i++;
	}
}

void	init_try_quotes_tools(t_try_quotes_tools *tools,
		char *line, int i, int *i_ptr)
{
	tools->start = *i_ptr;
	tools->begin_quote = line[i];
	tools->line = line;
	tools->i_ptr = i_ptr;
}

int	check_to_continue(char *line, int	*i)
{
	if (ft_strchr(" <>|()\t", line[*i]) != NULL
		|| ft_strncmp(&line[*i], "&&", 2) == 0)
		return (FALSE);
	return (TRUE);
}
