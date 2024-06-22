/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_env_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:59:20 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/28 10:08:01 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

/**
 * tries to insert expanded str into 
 * 
 * if expanded_str was empty, ?????
*/
t_expand_code	build_expanded_into_latest_strpart(t_parameter_pts_holder *p,
	t_quotes_part *latest_part, char **expanded_str, t_buffer *buffer)
{
	if ((*expanded_str)[0] != '\0')
	{
		insert_expanded_str_into_latest_part(*expanded_str,
			latest_part, p->tools, buffer);
		p->tools->i = p->tools->start;
		latest_part->built_expanded_into_latest_strpart = TRUE;
		if (latest_part->type != NOQUOTES)
			return (EXPANDED);
		cutoff_and_move_new_env(p, latest_part);
	}
	else
	{
		ft_strcpy(&latest_part->part[p->tools->start - 1],
			&latest_part->part[p->tools->i]);
		p->tools->i = p->tools->start - 1;
		free(*expanded_str);
		return (NOT_EXPANDED);
	}
	return (EXPANDED);
}
// printf("len %d\n", len);
// printf("remaining %s\n", p->remaining_new_env);

/**
 * if len after '$' == 0, create build empty string
 * 
*/
void	try_build_expanded_str(t_insert_expand_tools *tools,
	t_quotes_part *latest_part, char **expanded_str, t_buffer *buffer)
{
	char	*compare_key;
	char	*found_str;

	tools->len = tools->i - tools->start;
	if (tools->len == 0)
	{
		build_empty_str(expanded_str, buffer);
		return ;
	}
	else
	{
		compare_key = ft_substr(latest_part->part, tools->start, tools->len);
		if (!compare_key)
			clean_and_exit(MALLOC_ERROR, buffer);
		found_str = get_env_value(buffer->env_list, compare_key, NULL);
		if (!found_str)
			found_str = "";
		*expanded_str = ft_strdup(found_str);
		if (!*expanded_str)
			clean_and_exit(MALLOC_ERROR, buffer);
		free(compare_key);
		compare_key = NULL;
	}
}
// printf("expanded %s\n", *expanded_str);

void	handle_remaining_str_last(t_insert_expand_tools	*tools,
	t_parameter_pts_holder *p,
	t_quotes_part **str_part_lst, t_buffer *buffer)
{
	char	*new_str;

	new_str = ft_strdup(p->remaining_new_env);
	if (!new_str)
		clean_and_exit(MALLOC_ERROR, buffer);
	strpart_lstadd_back(str_part_lst,
		strpart_lstnew(new_str, NOQUOTES, buffer));
	strpart_lstlast(*str_part_lst)->shifted_due_to_env_lex_expand = TRUE;
	tools->i = 0;
}
// printf("remaining %s\n", p->remaining_new_env);

int	building(t_parameter_pts_holder *p,
	t_quotes_part *latest_part, char *expanded_str_old_ptr)
{
	try_build_expanded_str(p->tools, latest_part,
		&expanded_str_old_ptr, p->buffer);
	if (build_expanded_into_latest_strpart(p,
			latest_part, &expanded_str_old_ptr, p->buffer) == NOT_EXPANDED)
		return (NOT_EXPANDED);
	p->expanded_str = ft_strdup(strpart_lstlast(latest_part)->part);
	if (!p->expanded_str)
		clean_and_exit(MALLOC_ERROR, p->buffer);
	try_env_expand_to_lex_nodes(p, latest_part);
	free(p->expanded_str);
	if (p->remaining_new_env != NULL)
	{
		handle_remaining_str_last(p->tools, p, p->str_part_lst, p->buffer);
		free(p->remaining_new_env);
		p->remaining_new_env = NULL;
	}
	return (EXPANDED);
}

/**
 * insert expanded str into strpart
 *
 * unless found a multiple word variable
 * 
 * 
 * right now the basis of lexer works with strparts
 * parsing the quotes and nonqoutes consequtively, but these parts
 * get expanded parsed Dynamicly if neccecary
 * ______________________________________________________
 * Dynamicly
 * ______________________________________________________
 * if the $var gets expanded into multiple words.
 * this is the eetl(env expand to lexes)
 * 
 * could be added to a previous lex(first part)
 * a new lex created
 * 
 * After the expansion the following new strparts will also
 * still be following the dynamic way.
 * for instance; joining strpart to latest env expanded lex:
 * $var ="hi hello"
 * minishell>echo $var"cool"
 * lexes: <echo> <hi> <hellocool>
 *
 * ______________________________________________________
 * Staticly
 * ______________________________________________________
 * if dynamic expanding is not neccecary the parts will be joined
 * together after the loop (' ' encounterd or end or token)
 * this is the staticly joined way.
 * 
 * simple $var expansion is also with staticly
 * 
 * 
 */
int	build_expanded_part(t_parameter_pts_holder *p,
	t_quotes_part *latest_part, char *line_point)
{
	char	*expanded_str;

	expanded_str = NULL;
	if (latest_part->part[++p->tools->i] == '\0'
		&& !check_if_dollar_adjecent_to_new_quotes
		(&latest_part->part[p->tools->i - 1], line_point))
		return (NOT_EXPANDED);
	p->tools->start = p->tools->i;
	if (latest_part->part[p->tools->i] == '?')
	{
		building_errno_case(p, latest_part);
		return (EXPANDED);
	}
	else
	{
		while (special_char_list(latest_part->part[p->tools->i]) == 0
			&& latest_part->part[p->tools->i] != ' '
			&& latest_part->part[p->tools->i] != '\0')
			p->tools->i++;
	}
	return (building(p, latest_part, expanded_str));
}
// printf("new %s\n", p->remaining_new_env);
//printf("compare str %s, i %d, len %d, start %d\n"
// , compare_key, *i, len, start);
//printf("start %s\n", &latest_part->part[tools->i]);