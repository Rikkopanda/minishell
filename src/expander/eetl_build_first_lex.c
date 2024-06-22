/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eetl_build_first_lex.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:19:11 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/27 17:15:50 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*join_strparts_except_last(t_quotes_part *str_part_lst,
	t_buffer *buffer)
{
	int				str_len;
	char			*total_str;
	t_quotes_part	*cur_str_part;

	str_len = strpart_strlen(str_part_lst, TRUE);
	if (str_len <= 1)
		return ((char *)FALSE);
	total_str = malloc(sizeof(char) * str_len);
	if (!total_str)
		clean_and_exit(MALLOC_ERROR, buffer);
	total_str[0] = '\0';
	cur_str_part = str_part_lst;
	while (cur_str_part != NULL)
	{
		if (cur_str_part->next == NULL)
			break ;
		ft_strcat(total_str, cur_str_part->part);
		cur_str_part = cur_str_part->next;
	}
	return (total_str);
}

int	join_previous_parts_to_str(t_parameter_pts_holder *p,
	char	**totalstr, int *wild_card_quotes_check)
{
	char	*tmpstr;

	*wild_card_quotes_check = scan_strparts_quotes_for_wildcard_check
		(*p->str_part_lst);
	tmpstr = join_strparts_except_last(*p->str_part_lst, p->buffer);
	if (tmpstr == (char *)FALSE && *p->original_pre_env == '\0')
		return (ERROR);
	*totalstr = ft_strjoin_v2(tmpstr, p->original_pre_env);
	if (tmpstr != (char *)FALSE)
		free(tmpstr);
	if (!*totalstr)
		clean_and_exit(MALLOC_ERROR, p->buffer);
	return (SUCCESS);
}

void	build_new_lex(t_parameter_pts_holder *p,
	int *wild_card_quotes_check, char *totalstr)
{
	if (!*wild_card_quotes_check)
	{
		if (scan_and_try_wildcard(totalstr, p->buffer, FALSE) != MATCHING)
			lex_lstadd_back(&p->buffer->lexer_list,
				lex_lstnew(totalstr, WORD, p->buffer));
	}
	else
		lex_lstadd_back(&p->buffer->lexer_list,
			lex_lstnew(totalstr, WORD, p->buffer));
}

/**
 * no preceding spaces in expanded str.
 * lexes preceding
*/
void	build_default_case(t_parameter_pts_holder *p)
{
	char	*total_str;
	char	*total_str_2;
	int		wild_card_quotes_check;

	total_str = NULL;
	if (join_previous_parts_to_str(p, &total_str,
			&wild_card_quotes_check) == ERROR)
	{
		build_case_no_parts_to_join(p, wild_card_quotes_check);
		return ;
	}
	total_str_2 = ft_strjoin_v2(total_str, p->expanded_substr);
	if (total_str)
		free(total_str);
	if (!total_str_2)
		clean_and_exit(MALLOC_ERROR, p->buffer);
	if (lex_lstlast(p->buffer->lexer_list) == NULL
		|| lex_lstlast
		(p->buffer->lexer_list)->extra_space_if_new_strpart == TRUE
		|| lex_lstlast(p->buffer->lexer_list)->dynamic_joining == FALSE)
		build_new_lex(p, &wild_card_quotes_check, total_str_2);
	else
		build_case_glue_to_last_lex(p, total_str_2);
}

/**
 * aa$var$PWD
 * 
 * $var ->   "echo test 123"
 * "echo" -> "aaecho" --> <aaecho>
 * (exp_from_env=TRUE)
*/
void	build_first_expanded_lex(t_parameter_pts_holder *p,
	char *expanded_substr)
{
	if (p->eetl_tools->space_preceding_first_lex == TRUE)
	{
		preceding_space_case_build_lex(p, expanded_substr);
	}
	else if (lex_lstlast(p->buffer->lexer_list) == NULL)
	{
		build_default_case(p);
	}
	else if (lex_lstlast(p->buffer->lexer_list)->dynamic_joining == TRUE
		&& lex_lstlast
		(p->buffer->lexer_list)->extra_space_if_new_strpart == FALSE)
	{
		build_default_case(p);
	}
	else
	{
		build_default_case(p);
	}
}
// printf("case1\n");
// printf("total =%s\n", total_str);
// printf("lexlast: =%s\n", lex_lstlast(buffer->lexer_list)->word);
// printf("total =%s\n", total_str);
// printf("trimmed =%s\n", latest_part->part);
// printf("new part =%s\n", latest_part->part);