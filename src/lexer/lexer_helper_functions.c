/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:14:14 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/08/01 12:02:27 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * or if its space
*/
int	check_non_printable(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (ft_isprint(line[i]) == TRUE && line[i] != ' ')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	clear_part_lst(t_quotes_part *str_part_lst)
{
	t_quotes_part	*tmp;

	while (str_part_lst != NULL)
	{
		tmp = str_part_lst->next;
		if (str_part_lst->part != NULL)
		{
			free(str_part_lst->part);
			str_part_lst->part = NULL;
		}
		free(str_part_lst);
		str_part_lst = tmp;
	}
}

/**
 * target ptr will be replaced by expanded
*/
void	expand_str(char	**target_to_expand_ptr, char *str2, t_buffer *buffer)
{
	char	*target_tmp_str;

	(void)buffer;
	target_tmp_str = ft_strdup(*target_to_expand_ptr);
	if (!target_tmp_str)
		clean_and_exit(MALLOC_ERROR, buffer);
	free(*target_to_expand_ptr);
	*target_to_expand_ptr = ft_strjoin(target_tmp_str, str2);
	if (!*target_to_expand_ptr)
		clean_and_exit(MALLOC_ERROR, buffer);
	free(target_tmp_str);
}

/**
 * 
*/
int	check_dynamic_join_last_part(t_quotes_part	*str_part_lst,
	char *line, int	*i, t_buffer *buffer)
{
	if (str_part_lst == NULL)
		return (FALSE);
	if (check_last_lex_node_if_came_from_env(buffer) == TRUE
		&& check_if_strpart_will_expand(str_part_lst,
			&line[*i]) == FALSE
		&& strpart_lstlast(str_part_lst)->part[0] != '\0')
		return (TRUE);
	return (FALSE);
}

/**
 * 
*/
int	check_dynamic_join_post_expansion(t_quotes_part	*str_part_lst,
	t_buffer *buffer)
{
	if (str_part_lst == NULL)
		return (FALSE);
	if (last_strpart_shifted_for_env_expanded(str_part_lst) == TRUE
		|| ((strpart_lstlast(str_part_lst)
				->built_expanded_into_latest_strpart == TRUE
				&& check_last_lex_node_if_came_from_env(buffer) == TRUE)
			&& strpart_lstlast(str_part_lst)->part[0] != '\0'))
	{
		return (TRUE);
	}
	return (FALSE);
}
// printf("last one %s\n", strpart_lstlast(str_part_lst)->part);
