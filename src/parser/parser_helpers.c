/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:13:49 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/25 19:29:38 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	print_cmd_group_array(t_buffer *buffer)
{
	int		i;
	t_cmd	**array;

	array = buffer->group_start_cmd;
	i = 0;
	printf("\n");
	while (array[i] != NULL)
	{
		printf("i = %d\topen?=%d\tpersonal_cnt%d\n",
			i, array[i]->parenthesis_status,
			array[i]->parenthesis_cnt_personal);
		i++;
	}
	printf("\n");
	return (0);
}

int	check_if_operator(t_lexer	**lex_cur)
{
	if (*lex_cur == NULL)
		return (FALSE);
	if ((*lex_cur)->token_type == PIPE
		|| (*lex_cur)->token_type == AND_OPERATOR
		|| (*lex_cur)->token_type == OR_OPERATOR)
		return (TRUE);
	else
		return (FALSE);
}

int	check_parenthesis_after_word(
	t_lexer	**lex_cur)
{
	if ((*lex_cur) == NULL)
		return (EXIT);
	if ((*lex_cur)->token_type == PARENTHESIS_BEGIN)
	{
		return (SYNTAX_ERROR);
	}
	else
		return (NONE);
}

t_builtin	find_builtin(t_lexer *try_arg)
{
	const void	*ptr_array[7][2] = {
	{"echo", b_echo},
	{"cd", b_cd},
	{"pwd", b_pwd},
	{"export", b_export},
	{"unset", b_unset},
	{"env", b_env},
	{"exit", b_exit}
	};
	int			i;

	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(ptr_array[i][0], try_arg->word) == 0)
			return (ptr_array[i][1]);
		i++;
	}
	return (NULL);
}

int	move_in_out_nodes2(t_lexer	**redir_lst,
	t_lexer	**lex_cur, t_buffer *buffer)
{
	if ((*lex_cur)->next == NULL)
	{
		return (set_err_and_msg((*lex_cur)->token_type,
				*lex_cur, buffer), SYNTAX_ERROR);
	}
	else if ((*lex_cur)->next->token_type != WORD)
	{
		return (set_err_and_msg((*lex_cur)->token_type,
				*lex_cur, buffer), SYNTAX_ERROR);
	}
	else
	{
		(*lex_cur)->word = (*lex_cur)->next->word;
		(*lex_cur)->next->word = NULL;
		lexnode_to_redir_lst(redir_lst, lex_cur);
		*lex_cur = (*lex_cur)->next;
	}
	return (SUCCESS);
}
