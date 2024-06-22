/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_home.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:48:46 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/29 10:15:16 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

/**
 * handle own way oppose to bash:
 * ';'
 */
static int	check_after_home_char_before_env_case(int i,
	t_quotes_part *latest_part)
{
	if (latest_part->part[i] == ':' || latest_part->part[i] == ';')
		return (DONT_EXPAND_ENV);
	return (DO_EXPAND);
}

/**
 * shift i in case of ';'. In order to exclude it in expander
 * don't actually have to handle this
 * in case of syntax error????
 */
static int	check_after_home_char_for_home_expand(t_insert_expand_tools *tools,
		t_quotes_part *latest_part, t_buffer *buffer)
{
	(void)buffer;
	if (!(latest_part->part[tools->i] == '/'
			|| latest_part->part[tools->i] == ':'
			|| latest_part->part[tools->i] == '\0'
			|| latest_part->part[tools->i] == ';'))
		return (DONT_EXPAND_ALL);
	if (latest_part->part[tools->i] == ';')
		tools->i++;
	return (DO_EXPAND);
}

static void	expanding_home_and_inserting(t_insert_expand_tools *tools,
	t_quotes_part *latest_part, t_buffer *buffer)
{
	char	*expanded_str;

	expanded_str = ft_strdup(get_home_path(buffer));
	if (expanded_str == NULL)
		clean_and_exit(MALLOC_ERROR, buffer);
	if (*expanded_str == '\0')
		return ;
	insert_expanded_str_into_latest_part(expanded_str,
		latest_part, tools, buffer);
}

void	expand_home(t_parameter_pts_holder *p,
		t_quotes_part *latest_part)
{
	p->tools->i++;
	p->tools->start = p->tools->i;
	if (check_after_home_char_for_home_expand(p->tools, latest_part, p->buffer)
		== DONT_EXPAND_ALL)
		return ;
	p->tools->len = p->tools->i - p->tools->start;
	if (latest_part->part[p->tools->i] == '$'
		&& check_after_home_char_before_env_case(p->tools->i - 1, latest_part)
		!= DONT_EXPAND_ENV)
	{
		if (check_char_after_dollar(latest_part->part[p->tools->i + 1])
			== DONT_EXPAND_ALL)
			return ;
		if (build_expanded_part(p, latest_part,
				&latest_part->part[p->tools->i])
			== NOT_EXPANDED)
			return ;
	}
	expanding_home_and_inserting(p->tools, latest_part, p->buffer);
}
