/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   general_helpers.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rikverhoeven <rikverhoeven@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/16 09:53:09 by rikverhoeve   #+#    #+#                 */
/*   Updated: 2024/04/26 18:36:34 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "helper_functions.h"

int	cmd_lex_size(t_lexer	*lex_node)
{
	int	i;

	if (lex_node == NULL)
		return (0);
	i = 0;
	while (lex_node != NULL)
	{
		if (lex_node->token_type == PIPE)
			break ;
		lex_node = lex_node->next;
		if (lex_node == NULL)
			break ;
		i++;
	}
	return (i);
}

int	lex_size(t_lexer	*lex_node)
{
	int	i;

	i = 0;
	while (lex_node != NULL)
	{
		lex_node = lex_node->next;
		i++;
	}
	return (i);
}

void	free_lex_ptrs(t_buffer *buffer)
{
	t_lexer	**lex_ptrs;
	int		i;

	lex_ptrs = buffer->lex_ptrs;
	if (lex_ptrs == NULL)
		return ;
	i = 0;
	while (lex_ptrs[i] != NULL)
	{
		if (buffer->is_child == FALSE \
				&& lex_ptrs[i]->token_type == HEREDOC_RESOLVED)
			unlink(lex_ptrs[i]->word);
		if (lex_ptrs[i]->word != NULL)
			free(lex_ptrs[i]->word);
		free(lex_ptrs[i]);
		i++;
	}
	free(lex_ptrs);
	buffer->lex_ptrs = NULL;
}
