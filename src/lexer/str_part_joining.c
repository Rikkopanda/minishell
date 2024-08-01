/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_part_joining.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:19:12 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/08/01 12:02:27 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*join_strparts(t_quotes_part *str_part_lst,
	t_buffer *buffer, int *wild_card_quotes_check)
{
	int				str_len;
	char			*total_str;
	t_quotes_part	*cur_str_part;

	str_len = strpart_strlen(str_part_lst, FALSE);
	total_str = malloc(sizeof(char) * str_len);
	if (!total_str)
		clean_and_exit(MALLOC_ERROR, buffer);
	total_str[0] = '\0';
	cur_str_part = str_part_lst;
	while (cur_str_part != NULL)
	{
		scan_part_on_wildcard_quote_check(cur_str_part, wild_card_quotes_check);
		ft_strcat(total_str, cur_str_part->part);
		cur_str_part = cur_str_part->next;
	}
	return (total_str);
}

int	scan_strparts_quotes_for_wildcard_check(t_quotes_part *str_part_lst)
{
	int				wild_card_quotes_check;
	t_quotes_part	*cur_str_part;

	wild_card_quotes_check = 0;
	cur_str_part = str_part_lst;
	while (cur_str_part != NULL)
	{
		scan_part_on_wildcard_quote_check(cur_str_part,
			&wild_card_quotes_check);
		cur_str_part = cur_str_part->next;
	}
	return (wild_card_quotes_check);
}

void	assemble_together_parts(t_joining_vars *v,
	t_quotes_part *str_part_lst, t_buffer *buffer)
{
	v->last_lex = lex_lstlast(buffer->lexer_list);
	if (!v->last_lex)
		return ;
	v->wild_card_quotes_check = scan_strparts_quotes_for_wildcard_check
		(str_part_lst);
	v->tmp_str = join_strparts_except_last(str_part_lst, buffer);
	v->joined_strparts = ft_strjoin(v->tmp_str,
			strpart_lstlast(str_part_lst)->part);
	if (!v->joined_strparts)
		clean_and_exit(MALLOC_ERROR, buffer);
	if (v->tmp_str != (char *)FALSE)
		free(v->tmp_str);
	empty_and_reset_parts(str_part_lst);
}

/**
 * joins whole new str_part to last expanded lex(by way of env)
 * 
 * this is when a part has been expanded into multiple lexes
 * 
*/
void	join_latest_str_part_to_last_lex(t_quotes_part *str_part_lst,
	t_buffer *buffer)
{
	t_joining_vars	v;

	assemble_together_parts(&v, str_part_lst, buffer);
	if (v.last_lex->extra_space_if_new_strpart == FALSE
		&& v.last_lex->dynamic_joining == TRUE)
		glue_str_to_part(v.last_lex, v.joined_strparts, buffer,
			v.wild_card_quotes_check);
	else
	{
		if (fresh_lex_node_build(v.joined_strparts, buffer,
				v.wild_card_quotes_check) == NONE)
			return ;
	}
	free(v.joined_strparts);
	lex_lstlast(buffer->lexer_list)->dynamic_joining = TRUE;
}
// printf("join latest dynamic %s\n", joined_strparts);
// printf("lateststrpart %s\n", strpart_lstlast(str_part_lst)->part);
// if (last_lex->waiting_for_strpart)
//printf("dynamicly joined\n");
