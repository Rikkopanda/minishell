/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:50:22 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/21 16:24:38 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	check_for_hidden_content(char *name)
{
	if (name[0] == '.')
		return (1);
	return (0);
}

void	init_part_build_tools(t_index_tools *tools, int *i)
{
	tools->start = *i;
	tools->i_ptr = i;
}
