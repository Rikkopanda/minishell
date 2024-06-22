/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eetl_create_cutoff_new_env.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rverhoev <rverhoev@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/25 18:50:41 by rverhoev      #+#    #+#                 */
/*   Updated: 2024/04/29 17:25:55 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	create_cutoff_and_move(t_parameter_pts_holder *p,
	t_quotes_part *latest_part, int cutoff_new_env)
{
	int	len;

	len = ft_strlen(latest_part->part) - cutoff_new_env;
	p->remaining_new_env = ft_substr
		(latest_part->part, cutoff_new_env, len);
	if (!p->remaining_new_env)
		clean_and_exit(MALLOC_ERROR, p->buffer);
	trim_str(cutoff_new_env, latest_part->part);
}

void	cutoff_and_move_new_env(t_parameter_pts_holder *p,
	t_quotes_part *latest_part)
{
	int	i;
	int	cutoff_new_env;

	i = 0;
	cutoff_new_env = -1;
	while (latest_part->part[i] != '\0')
	{
		if (latest_part->part[i] == '$'
			&& (latest_part->part[i + 1] != ' '
				&& latest_part->part[i + 1] != '\t'))
		{
			cutoff_new_env = i;
			break ;
		}
		i++;
	}
	if (cutoff_new_env != -1)
		create_cutoff_and_move(p, latest_part, cutoff_new_env);
}
// printf("pre_cutoff: %s \n", latest_part->part);
//&& latest_part->part[i + 1] != '\0'
