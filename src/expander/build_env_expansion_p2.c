/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_env_expansion_p2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:05:22 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/27 16:06:48 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	building_errno_case(t_parameter_pts_holder *p,
	t_quotes_part *latest_part)
{
	char	*expanded_str;

	expanded_str = NULL;
	p->tools->len = 1;
	expand_errno_case(&expanded_str, p->tools, p->buffer);
	insert_expanded_str_into_latest_part(expanded_str,
		latest_part, p->tools, p->buffer);
	cutoff_and_move_new_env(p, latest_part);
	if (p->remaining_new_env != NULL)
	{
		handle_remaining_str_last(p->tools, p, p->str_part_lst, p->buffer);
		free(p->remaining_new_env);
		p->remaining_new_env = NULL;
	}
}
