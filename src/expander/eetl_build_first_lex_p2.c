/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eetl_build_first_lex_p2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:43:08 by rverhoev          #+#    #+#             */
/*   Updated: 2024/04/27 14:43:54 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

//join preceding except expanded part and lexnew
//lexnew with expanded part
void	preceding_space_case_build_lex(t_parameter_pts_holder *p,
	char *expanded_substr)
{
	char	*new_str;

	new_str = ft_strdup(expanded_substr);
	if (!new_str)
		clean_and_exit(MALLOC_ERROR, p->buffer);
	build_preceding_strpart_into_lex(p);
	lex_lstadd_back(&p->buffer->lexer_list,
		lex_lstnew(new_str, WORD, p->buffer));
	lex_lstlast(p->buffer->lexer_list)->dynamic_joining = TRUE;
}
// printf("total if start is ' ' =%s\n", total_str);

void	joining_strpart_to_env_expanded_lex(t_parameter_pts_holder *p,
	t_buffer *buffer)
{
	char	*total_str;

	total_str = ft_strjoin_v2(lex_lstlast(buffer->lexer_list)->word,
			p->expanded_substr);
	if (!total_str)
		clean_and_exit(MALLOC_ERROR, buffer);
	lex_lstlast(buffer->lexer_list)->word = total_str;
}

void	build_case_no_parts_to_join(t_parameter_pts_holder *p,
	int wild_card_quotes_check)
{
	char	*total_str_2;
	char	*total_str_3;

	total_str_2 = ft_strdup(p->expanded_substr);
	if (!total_str_2)
		clean_and_exit(MALLOC_ERROR, p->buffer);
	if (lex_lstlast(p->buffer->lexer_list) == NULL
		|| lex_lstlast
		(p->buffer->lexer_list)->extra_space_if_new_strpart == TRUE
		|| lex_lstlast(p->buffer->lexer_list)->dynamic_joining == FALSE)
		build_new_lex(p, &wild_card_quotes_check, total_str_2);
	else
	{
		total_str_3 = ft_strjoin_v2(lex_lstlast
				(p->buffer->lexer_list)->word, total_str_2);
		if (!total_str_3)
			clean_and_exit(MALLOC_ERROR, p->buffer);
		free(total_str_2);
		free(lex_lstlast(p->buffer->lexer_list)->word);
		lex_lstlast(p->buffer->lexer_list)->word = total_str_3;
	}
}

void	build_case_glue_to_last_lex(t_parameter_pts_holder *p,
	char *total_str_2)
{
	char	*total_str_3;

	total_str_3 = ft_strjoin_v2(lex_lstlast
			(p->buffer->lexer_list)->word, total_str_2);
	free(total_str_2);
	if (!total_str_3)
		clean_and_exit(MALLOC_ERROR, p->buffer);
	free(lex_lstlast(p->buffer->lexer_list)->word);
	lex_lstlast(p->buffer->lexer_list)->word = total_str_3;
}

void	build_preceding_strpart_into_lex(t_parameter_pts_holder *p)
{
	int		wild_card_quotes_check;
	char	*totalstr;

	if (join_previous_parts_to_str(p, &totalstr,
			&wild_card_quotes_check) == ERROR)
		return ;
	build_new_lex(p, &wild_card_quotes_check, totalstr);
}
// printf("lexlast =%s\n", lex_lstlast(p->buffer->lexer_list)->word);