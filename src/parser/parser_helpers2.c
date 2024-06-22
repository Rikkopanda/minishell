/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:00:10 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/20 10:02:07 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_cmd_array(int len, t_buffer *buffer)
{
	int	i;

	i = 0;
	while (i <= len + SPACE_FOR_NEW_CMD)
	{
		buffer->group_start_cmd[i] = NULL;
		i++;
	}
}
