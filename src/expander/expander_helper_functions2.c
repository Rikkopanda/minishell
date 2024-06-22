/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helper_functions2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:44:43 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/28 10:07:53 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	check_if_strpart_will_expand(t_quotes_part *str_part_lst,
	char *line_point)
{
	t_quotes_part			*latest_part;
	t_insert_expand_tools	tools;

	tools.i = 0;
	latest_part = strpart_lstlast(str_part_lst);
	if (latest_part->type == SINGLE_QUOTE)
		return (FALSE);
	while (latest_part->part[tools.i] != '\0')
	{
		if (env_expand_check(&tools, latest_part, line_point))
			return (TRUE);
		else
			tools.i++;
	}
	return (FALSE);
}

int	check_if_dollar_adjecent_to_new_quotes(char *checking_strpart_point,
	char *line_point)
{
	if (*line_point == '\0')
		return (FALSE);
	else if ((*line_point == '"'
			|| *line_point == '\'')
		&& *checking_strpart_point == '$')
	{
		return (TRUE);
	}
	return (FALSE);
}
// printf("hi again %c and %c\n", *checking_strpart_point, *line_point);
