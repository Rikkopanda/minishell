/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:01:42 by rverhoev          #+#    #+#             */
/*   Updated: 2024/04/28 10:09:19 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
	token after IN or OUT should be a WORD(file)
*/
static int	try_in_out_token(t_cmd	**cmd_cur,
	t_lexer	**lex_cur, t_buffer *buffer)
{
	int	status;

	status = SUCCESS;
	if (*lex_cur == NULL)
		return (EXIT);
	else if ((*lex_cur)->token_type == IN
		|| (*lex_cur)->token_type == HEREDOC)
		status = move_in_out_nodes2(&(*cmd_cur)->in_lst, lex_cur, buffer);
	else if ((*lex_cur)->token_type == OUT
		|| (*lex_cur)->token_type == APPEND)
	{
		if (move_in_out_nodes2(&(*cmd_cur)->out_lst, lex_cur, buffer)
			== SYNTAX_ERROR)
			return (SYNTAX_ERROR);
		status = try_ending_group(lex_cur, buffer);
		if (status == PARENTHESIS_END && check_if_operator(&(*lex_cur)->next)
			== TRUE)
			status = try_pipe_or_logic_token(cmd_cur, lex_cur, buffer);
	}
	return (status);
}

static int	try_word_token(t_cmd	**cmd_cur,
	t_lexer	**lex_cur, t_buffer *buffer)
{
	static int	i;
	t_lexer		*tmp;

	(void)buffer;
	if (*lex_cur == NULL)
		return (EXIT);
	if ((*lex_cur)->token_type == WORD)
	{
		(*cmd_cur)->builtin = find_builtin(*lex_cur);
		while ((*lex_cur)->token_type == WORD)
		{
			if (check_parenthesis_after_word(&(*lex_cur)->next)
				== SYNTAX_ERROR)
				return (set_err_and_msg((*lex_cur)->token_type,
						*lex_cur, buffer), SYNTAX_ERROR);
			tmp = *lex_cur;
			*lex_cur = (*lex_cur)->next;
			tmp->next = NULL;
			lex_lstadd_back(&(*cmd_cur)->arg_lst, tmp);
			if ((*lex_cur) == NULL)
				break ;
			i++;
		}
	}
	return (SUCCESS);
}
/*
	// if (check_parenthesis_after_word(&(*lex_cur)->next)
	// 	== SYNTAX_ERROR)
	// 	return (set_err_and_msg((*lex_cur)->token_type,
	// 			*lex_cur, buffer), SYNTAX_ERROR);
	printf("cur %s\n", (*lex_cur)->word);
	tmp = *lex_cur;
	tmp->next = NULL;
	lex_lstadd_back(&(*cmd_cur)->arg_lst, tmp);
	*lex_cur = (*lex_cur)->next;
	if ((*lex_cur) == NULL)
		break ;
	else if ((*lex_cur)->token_type == WORD)
	{
		i++;
		continue;
	}
	// try_ending_group(lex_cur, buffer);
	// printf("cur %s\n", (*lex_cur)->word);
	// if (check_if_operator(lex_cur) == FALSE && *lex_cur != NULL)
	// 	return (set_err_and_msg((*lex_cur)->token_type,
	// 			*lex_cur, buffer), SYNTAX_ERROR);
*/

// printf("hello2\n");
// if ((*cmd_cur)->arguments == NULL)
// 	init_cmd(cmd_cur, lex_cur, &i);
// printf("hello3\n");
// (*cmd_cur)->arguments[i] = (*lex_cur)->word;
// i = &(*cmd_cur)->arg_index;

/**
 * when a operator is found; &&, || or |. then a new cmd is made
 * try_parenthesis doesnt do this
 * 
 * sets
 * 
 * closes pare status if neccecary
*/
int	try_parenthesis(t_lexer **lex_cur, t_buffer *buffer)
{
	if ((*lex_cur) == NULL)
		return (EXIT);
	if ((*lex_cur)->token_type == PARENTHESIS_BEGIN)
	{
		buffer->cmd_group_logic_status = PARENTHESIS_BEGIN;
		buffer->cmd_group_temp_cnt++;
		if ((*lex_cur)->next == NULL)
			return (set_err_and_msg((*lex_cur)->token_type,
					*lex_cur, buffer), SYNTAX_ERROR);
		return ((*lex_cur) = (*lex_cur)->next, PARENTHESIS_BEGIN);
	}
	else if ((*lex_cur)->token_type == PARENTHESIS_END)
	{
		if (buffer->group_cmds_i == -1
			|| decrement_all_cmd_cnts(buffer) == NONE_DECREMENTED)
			return (set_err_and_msg((*lex_cur)->token_type,
					*lex_cur, buffer), SYNTAX_ERROR);
		if ((*lex_cur)->next != NULL)
			if ((*lex_cur)->next->token_type == WORD)
				return (set_err_and_msg((*lex_cur)->token_type,
						*lex_cur, buffer), SYNTAX_ERROR);
		buffer->cmd_group_logic_status = PARENTHESIS_END;
		return ((*lex_cur) = (*lex_cur)->next, PARENTHESIS_END);
	}
	return (NONE);
}
// printf("cnt %d - 1\n", buffer->cmd_group_temp_cnt);
// printf("hello %d  \n", (*lex_cur)->token_type);

/**
 * checks current token to see if it is either
 * a PIPE or one of the 2 logic tokens; AND, OR
 * 
 * checks syntax error
 * sets 'logic type' of current command
 * builds new cmd
*/
int	try_pipe_or_logic_token(t_cmd	**cmd_cur,
	t_lexer	**lex_cur, t_buffer *buffer)
{
	if ((*lex_cur) == NULL)
		return (EXIT);
	if (check_if_operator(lex_cur) == TRUE)
	{
		if ((*lex_cur)->next == NULL)
			return (set_err_and_msg((*lex_cur)->token_type,
					*lex_cur, buffer), SYNTAX_ERROR);
		else if ((*cmd_cur)->arg_lst == NULL
			|| ((*lex_cur)->next->token_type != WORD
				&& (*lex_cur)->next->token_type != PARENTHESIS_BEGIN
				&& (*lex_cur)->next->token_type != IN))
			return (set_err_and_msg((*lex_cur)->token_type,
					*lex_cur, buffer), SYNTAX_ERROR);
		(*cmd_cur)->next = cmd_lstnew(NULL, (*lex_cur)->token_type, buffer);
		(*cmd_cur) = (*cmd_cur)->next;
		(*lex_cur) = (*lex_cur)->next;
		if (try_beginning_group(lex_cur, buffer) == SYNTAX_ERROR)
			return (SYNTAX_ERROR);
		increment_all_open_groups_cnt(buffer);
		(*cmd_cur)->parenthesis_cnt_personal = buffer->cmd_group_temp_cnt;
		buffer->cmd_group_temp_cnt = 0;
		increase_lenght_previous_groups(buffer);
		try_add_cmd_to_ptr_array(*cmd_cur, buffer);
	}
	return (SUCCESS);
}

/*
	returns when it reaches end of lex nodes or when syntax error occurs.

	at beginning parenthesis token, tmp_parentethis is incremented,
	the group_logic_cnt of each 'open' group is incremented,
	this is personal for each group and the new group,
	which is assigned to the beginning cmd.

	at the end all counters must be zero (equal amount of '('  and ')')
	So all are closed.
*/
void	parser(t_cmd **command_lst, t_lexer	*lex_cur, t_buffer *buffer)
{
	t_cmd	*cmd_cur;

	init_cmd_group_logic(buffer);
	*command_lst = cmd_lstnew(NULL, NONE, buffer);
	cmd_cur = *command_lst;
	if (try_beginning_group(&lex_cur, buffer) == SYNTAX_ERROR)
		return ;
	cmd_cur->parenthesis_cnt_personal = buffer->cmd_group_temp_cnt;
	if (buffer->cmd_group_logic_status == PARENTHESIS_BEGIN)
		try_add_cmd_to_ptr_array(cmd_cur, buffer);
	while (lex_cur != NULL)
	{
		if (try_in_out_token(&cmd_cur, &lex_cur, buffer) == SYNTAX_ERROR)
			return ;
		if (try_parenthesis(&lex_cur, buffer) == SYNTAX_ERROR)
			return ;
		if (try_word_token(&cmd_cur, &lex_cur, buffer) == SYNTAX_ERROR)
			return ;
		if (try_pipe_or_logic_token(&cmd_cur, &lex_cur, buffer) > SUCCESS)
			return ;
	}
	check_group_cnts(buffer, &lex_cur);
}
//printf("token = %d, word = %s\n", lex_cur->token_type, lex_cur->word);
// print_lex(cmd_cur->redirections_lst);
// print_lex(lex_cur);