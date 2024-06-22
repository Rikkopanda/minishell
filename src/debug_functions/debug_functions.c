/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:21:46 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/26 11:51:27 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_strparts(t_quotes_part *cur_strpart)
{
	printf("_____________\n");
	while (cur_strpart != NULL)
	{
		printf("part:%s\t", cur_strpart->part);
		cur_strpart = cur_strpart->next;
	}
	printf("\n_____________\n");
}

static void	print_lex_p2(t_lexer *lex_cur)
{
	if (lex_cur->token_type == AND_OPERATOR)
		dprintf(2, "<AND>");
	else if (lex_cur->token_type == OR_OPERATOR)
		dprintf(2, "<OR>");
	else if (lex_cur->token_type == PARENTHESIS_BEGIN)
		dprintf(2, "< ( >");
	else if (lex_cur->token_type == PARENTHESIS_END)
		dprintf(2, "< ) >");
	else if (lex_cur->token_type == APPEND)
		dprintf(2, "<APPEND>");
	else
		dprintf(2, "<%s>", lex_cur->word);
}

void	print_lex(t_lexer *lex_lst)
{
	t_lexer	*lex_cur;

	dprintf(2, "LEX:\t");
	lex_cur = lex_lst;
	while (lex_cur != NULL)
	{
		if (lex_cur->token_type == PIPE)
			dprintf(2, "<PIPE>");
		else if (lex_cur->token_type == IN)
			dprintf(2, "<IN>");
		else if (lex_cur->token_type == OUT)
			dprintf(2, "<OUT>");
		else if (lex_cur->token_type == HEREDOC)
			dprintf(2, "<HEREDOC>");
		else
			print_lex_p2(lex_cur);
		lex_cur = lex_cur->next;
	}
	dprintf(2, "\n");
}

void	print_lex_ptrs(t_lexer **lex_arr)
{
	int	i;

	i = 0;
	while (lex_arr[i])
	{
		dprintf(2, "%p->word %s\n", lex_arr[i], lex_arr[i]->word);
		i++;
	}
}

void	check_cmd_position(t_cmd **cmd_current, t_buffer *buffer)
{
	int		j;
	t_cmd	*cmd_curry;

	j = 0;
	cmd_curry = buffer->cmd_list;
	while (cmd_curry != *cmd_current && cmd_curry != NULL)
	{
		j++;
		cmd_curry = cmd_curry->next;
	}
}
