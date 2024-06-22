/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_main.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rverhoev <rverhoev@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/18 13:15:47 by rverhoev      #+#    #+#                 */
/*   Updated: 2024/04/26 18:53:28 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
	puts either a token or a word into the next node
	handling newlines also needed??

	tabs:
	echo		aaa		   		
*/
int	lexer(char *line, t_buffer *buffer)
{
	int		len;
	int		i;
	int		start;

	if (check_non_printable(line) == TRUE)
	{
		free(line);
		buffer->input_line = NULL;
		return (ERROR);
	}
	i = 0;
	len = ft_strlen(line);
	while (i <= len)
	{
		start = i;
		try_word(&start, line, &i, buffer);
		try_tokens(line, &i, buffer);
		if (i == start)
			break ;
	}
	buffer->lex_ptrs = save_lex_ptrs(buffer->lexer_list, buffer);
	return (0);
}
//printf("i %d, start %d.  %s\n", i, start, &line[i]);