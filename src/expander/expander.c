/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:26:29 by rverhoev          #+#    #+#             */
/*   Updated: 2024/04/29 10:22:58 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

/**
 * $(adf)   ->   into command "adf"
 * something for lexer?
 *
 *
 *  $)adf     -> unexpected token
 * 	#
 * 	@
 *
 * 	${adf -> input prompt
 * 	/
 * 	$%adf ->  keep as is   $%adf
 * 	:
 * 	.
 * 	}
 *
 *  implement own logic also because mimicing bash is not necceracy
 */
int	env_expand_check(t_insert_expand_tools	*tools,
	t_quotes_part *latest_part, char *line_point)
{
	if (latest_part->part[tools->i] == '$'
		&& latest_part->part[tools->i + 1] == '\0'
		&& check_if_dollar_adjecent_to_new_quotes
		(&latest_part->part[tools->i], line_point) != TRUE)
		return (FALSE);
	else if ((latest_part->part[tools->i] == '$'
			&& check_char_after_dollar
			(latest_part->part[tools->i + 1]) == DO_EXPAND
			&& latest_part->part[tools->i + 1] != ' '
			&& if_dollar_is_last_and_no_following_strparts
			(&latest_part->part[tools->i], line_point) == FALSE)
		|| check_if_dollar_adjecent_to_new_quotes
		(&latest_part->part[tools->i], line_point))
		return (TRUE);
	else
		return (FALSE);
}
// printf("hi %s and %s\n", &latest_part->part[tools->i], line_point);

/**
 * parses the last strpart and changes its
 * str with expanded str if it finds a variable
 *
 * ~;
 * expands into home path
 *
 * $VAR;
 * expands to whatever content
 *
 * env expanded lex;
 * in the env expander eventually, when it expands into new lexes,
 * the first expanded part of env str is remained on last lex,
 * after a ' ' an new lex is made,
 * the str of this is cut off of previous last lex.
 */
void	try_expander(t_quotes_part **str_part_lst,
	t_buffer *buffer, char *line_point)
{
	t_quotes_part			*latest_part;
	t_insert_expand_tools	tools;
	t_parameter_pts_holder	p;

	put_pointers_in_holder_1(&p, &tools, str_part_lst, buffer);
	init_index_tools(&tools);
	p.remaining_new_env = NULL;
	latest_part = strpart_lstlast(*str_part_lst);
	if (latest_part == NULL)
		return ;
	if (latest_part->type == SINGLE_QUOTE)
		return ;
	while (latest_part->part[tools.i] != '\0')
	{
		if (latest_part->part[tools.i] == '~' && tools.i == 0
			&& latest_part->type == NOQUOTES)
			expand_home(&p, latest_part);
		else if (env_expand_check(&tools, latest_part, line_point))
			build_expanded_part(&p, latest_part, line_point);
		else
			tools.i++;
		latest_part = strpart_lstlast(*str_part_lst);
	}
}
// printf("now %d\n", latest_part->part[tools.i]);
// print_lex(buffer->lexer_list);
// printf("string %s\n", &latest_part->part[tools.i]);
// printf("char %s\n", &latest_part->part[tools.i]);
// printf("%d i,  %s \n", tools.i, latest_part->part);