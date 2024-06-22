/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eetl_tools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:16:20 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/25 18:51:34 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	check_if_last_expansion(char *expand_str_point)
{
	int	i;

	i = 0;
	while (expand_str_point[i] == ' ' || expand_str_point[i] == '\t')
		i++;
	if (expand_str_point[i] == '\0')
		return (TRUE);
	return (FALSE);
}

/**
 * preceding to first expanded lex
*/
void	parse_preceding_spaces(char	*expanded_str,
	t_insert_expand_tools	*eetl_tools)
{
	while (expanded_str[eetl_tools->i] == ' '
		|| expanded_str[eetl_tools->i] == '\t')
	{
		eetl_tools->i += SKIP_SPACE_CHAR;
		eetl_tools->space_preceding_first_lex = TRUE;
	}
}

/**
 * expand if spaces present
*/
int	check_for_multiple_words_or_spaces(char	*expanded_str)
{
	int	expand_lexes_cnt;
	int	i;

	i = 0;
	expand_lexes_cnt = 0;
	while (expanded_str[i] != '\0')
	{
		if (expanded_str[i] == ' ' || expanded_str[i] == '\t')
		{
			while (expanded_str[i] == ' ' || expanded_str[i] == '\t')
				i++;
			if (expanded_str[i] != '\0')
			{
				expand_lexes_cnt++;
				i++;
			}
			else if (expanded_str[i] == '\0')
				return (TRIM_EXPANDED_SINGLE_WORD);
		}
		else
			i++;
	}
	return (expand_lexes_cnt);
}
// printf("expanded %s\n", expanded_str);

/**
 * trim str starting from j
*/
void	trim_str(int j, char *str)
{
	while (str[j] != '\0')
	{
		str[j] = '\0';
		j++;
	}
}

void	build_empty_str(char **expanded_str, t_buffer *buffer)
{
	char	*found_str;

	found_str = "";
	*expanded_str = ft_strdup(found_str);
	if (!*expanded_str)
		clean_and_exit(MALLOC_ERROR, buffer);
}
