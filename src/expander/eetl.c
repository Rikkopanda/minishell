/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eetl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 10:04:38 by rverhoev          #+#    #+#             */
/*   Updated: 2024/04/25 19:24:35 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

/**
 * 	make expander loop have str_part_str resume correctly
 * 
 * aa$var$PWD
 * $var ->   "echo test 123"
 * "echo" -> "aaecho" --> <aaecho>
 * 
 * --> + <test> <123>
 * (exp_from_env=TRUE)
 * 
 * "aa$var$PWD" -> remaining = "$PWD"
 * 
 * "$PWD" -> add strpart new
 * (shifted due to env_lex_expand=TRUE)
*/
// void	handle_remaining_str(t_insert_expand_tools	*tools,
// 	char *original_whole_str,
// 	t_quotes_part **str_part_lst, t_buffer *buffer)
// {
// 	int		total_len;
// 	int		new_start;
// 	int		new_len;
// 	char	*remaining_strpart;

// 	total_len = ft_strlen(original_whole_str);
// 	new_start = tools->start + tools->len;
// 	new_len = total_len - new_start;
// 	remaining_strpart = ft_substr(original_whole_str, new_start, new_len);
// 	if (!remaining_strpart)
// 		clean_and_exit(MALLOC_ERROR, buffer);
// 	strpart_lstadd_back(str_part_lst,
// 		strpart_lstnew(remaining_strpart, NOQUOTES, buffer));
// 	strpart_lstlast(*str_part_lst)->shifted_due_to_env_lex_expand = TRUE;
// }
// printf("original_whole_str %s\n", original_whole_str);
// printf("remaining %s\n", remaining_strpart);

/**
 * aa$var$PWD
 * $var ->   "echo test 123"
 * "echo" -> "aaecho" --> <aaecho>
 * 
 * --> + <test> <123>
 * (exp_from_env=TRUE)
 * 
*/
void	build_more_expanded_lexes(t_parameter_pts_holder *p,
	char *expanded_str, t_buffer *buffer)
{
	char	*expanded_substr;

	expanded_substr = ft_substr(expanded_str,
			p->eetl_tools->start, p->eetl_tools->len);
	if (scan_and_try_wildcard(expanded_substr, buffer, FALSE) != MATCHING)
		lex_lstadd_back(&buffer->lexer_list,
			lex_lstnew(expanded_substr, WORD, buffer));
	lex_lstlast(buffer->lexer_list)->dynamic_joining = TRUE;
	if (p->eetl_tools->space_after_last_lex == TRUE)
		lex_lstlast(buffer->lexer_list)->extra_space_if_new_strpart = TRUE;
}
//	eetl_tools->start ,eetl_tools->len);
// printf("expanded 2nd %s\n", expanded_substr);

void	empty_and_reset_parts(t_quotes_part *cur_part)
{
	while (cur_part != NULL)
	{
		trim_str(0, cur_part->part);
		cur_part = cur_part->next;
	}
}

void	eetl_build_lex(t_parameter_pts_holder *p)
{
	p->expanded_substr = NULL;
	p->original_pre_env = NULL;
	if (p->eetl_tools->eetl_build_lex_i == 0)
	{
		p->expanded_substr = ft_substr(p->expanded_str,
				p->eetl_tools->start, p->eetl_tools->len);
		p->original_pre_env = ft_substr
			(p->latest_part->part, 0, p->tools->start - 1);
		if (p->expanded_substr == NULL || p->original_pre_env == NULL)
			clean_and_exit(MALLOC_ERROR, p->buffer);
		build_first_expanded_lex(p, p->expanded_substr);
		empty_and_reset_parts(*p->str_part_lst);
		free(p->expanded_substr);
		free(p->original_pre_env);
	}
	else
	{
		build_more_expanded_lexes(p, p->expanded_str, p->buffer);
		empty_and_reset_parts(*p->str_part_lst);
	}
}
// print_lex(p->buffer->lexer_list);
// printf("after first built\n");
// printf("preceding %s\n", original_pre_env);

int	space_after_last_lex_check(char *expanded_str,
	t_insert_expand_tools *eetl_tools)
{
	if ((expanded_str[eetl_tools->i] == ' '
			|| expanded_str[eetl_tools->i] == '\t')
		&& check_if_last_expansion(&expanded_str[eetl_tools->i]))
		return (TRUE);
	else
		return (FALSE);
}

/**
 * 
 * env expand to lexes = eetl
 * 
 * _______________________________________________________________________
 * 
 * first env expanded lex:
 * if only 1 strpart? insert it
 * if multiple previous strparts, concat it to last one and lexnew
 * 
 * 
 * example: var="ls -l -a"
 * $var$PWD    --->   <ls> <-l> <-a$PWD>
 * 
 * the remaining str after('$PWD') has to be concatted to last env expanded lex
 * this $PWD will be expanded in next round of try_expander()
 * after try_expander() it will be dynamicly concatted
 * 
 * second and consecutives env expanded lexes:
 * lexnew and add with expanded str
 * set env_exp_lexes bool so that a following strpart can be dynamicly joined
 * 
 * 
 * env expand to lexes tools = eetl_tools
 * space padding decided with bools instead of index shifting?
*/
int	try_env_expand_to_lex_nodes(t_parameter_pts_holder *p,
	t_quotes_part *latest_part)
{
	t_insert_expand_tools	eetl_tools;

	if (check_for_multiple_words_or_spaces(p->expanded_str) == NO_ENV_EXPAND
		|| latest_part->type == DOUBLE_QUOTE)
		return (NOT_EXPANDED);
	init_index_tools(&eetl_tools);
	put_pointers_in_holder_2(p, &eetl_tools, latest_part, p->expanded_str);
	while (p->expanded_str[eetl_tools.i] != '\0')
	{
		reset_eetl_conditions(&eetl_tools);
		if (eetl_tools.eetl_build_lex_i == 0)
			parse_preceding_spaces(p->expanded_str, &eetl_tools);
		else if (parse_between_and_after_spaces(p->expanded_str,
				&eetl_tools) == END)
			break ;
		eetl_tools.start = eetl_tools.i;
		eetl_parse_word(p->expanded_str, &eetl_tools);
		if (space_after_last_lex_check(p->expanded_str, &eetl_tools))
			eetl_tools.space_after_last_lex = TRUE;
		eetl_tools.len = eetl_tools.i - eetl_tools.start;
		eetl_build_lex(p);
		eetl_tools.eetl_build_lex_i++;
	}
	return (EXPANDED);
}
// print_lex(p->buffer->lexer_list);
