/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:16:19 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/22 21:32:35 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

/**
 * using tools indexes to place correctly in original str
 * example: strpart = aa$PWD
 * expander started parsing at $
 * aa remains
 * and so expanded($PWD) comes at tools->i
 * '$PWD' text lenght is subtracted from total lenght
 *
 * concat expanded onto latest part
 */
void	insert_expanded_str_into_latest_part(char *expanded_str,
	t_quotes_part *latest_part, t_insert_expand_tools *tools, t_buffer *buffer)
{
	char	*new_str;
	int		len;
	int		i;

	len = ((ft_strlen(expanded_str))
			+ ft_strlen(latest_part->part)
			+ EXTRA_SIZE_FOR_TERMINATOR - tools->len);
	new_str = malloc(sizeof(char) * len);
	if (!new_str)
		clean_and_exit(MALLOC_ERROR, buffer);
	i = 0;
	while (i < len)
		new_str[i++] = '\0';
	ft_strlcpy(new_str, &latest_part->part[0], tools->start);
	ft_strcat(new_str, expanded_str);
	ft_strcat(new_str, &latest_part->part[tools->i]);
	free(latest_part->part);
	free(expanded_str);
	latest_part->part = new_str;
}
//printf("expanded str %s %s %d\n", expanded_str, new_str, len);