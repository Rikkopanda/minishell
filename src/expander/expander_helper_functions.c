/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helper_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:55:24 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/20 10:32:44 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	if_dollar_is_last_and_no_following_strparts(char *checking_strpart_point,
	char *line_point)
{
	if (*line_point == '\0'
		&& *(checking_strpart_point + 1) == '\0')
	{
		return (TRUE);
	}
	return (FALSE);
}

int	check_char_after_dollar(char chr)
{
	if (chr == '}' || chr == '{' || chr == '~' || chr == '\''
		|| chr == '.' || chr == ',' || chr == ';' || chr == ':'
		|| chr == '[' || chr == ']' || chr == '+' || chr == '='
		|| chr == '`')
		return (DONT_EXPAND_ALL);
	return (DO_EXPAND);
}

void	init_index_tools(t_insert_expand_tools *tools)
{
	tools->i = 0;
	tools->eetl_build_lex_i = 0;
	tools->len = 0;
	tools->start = 0;
}

int	special_char_list(char check_char)
{
	if ((check_char >= ' ' && check_char <= '/')
		|| (check_char >= '[' && check_char <= '`')
		|| (check_char >= '{' && check_char <= '~')
		|| (check_char >= ':' && check_char <= '@'))
		return (1);
	return (0);
}

void	expand_errno_case(char **expanded_str,
	t_insert_expand_tools *tools, t_buffer *buffer)
{
	tools->i++;
	*expanded_str = ft_itoa(buffer->exit_status_saved);
	if (!*expanded_str)
		clean_and_exit(MALLOC_ERROR, buffer);
}
