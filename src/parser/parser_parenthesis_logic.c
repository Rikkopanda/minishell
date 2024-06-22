/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parenthesis_logic.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:11:42 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/27 16:15:21 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * parses a pottentially multitude of 
 * beginning parenthesis '('
 * 
 * checks wrongly placed
 * ending parenthesis syntax error:  ( ) ( (
 * among other syntax checks
*/
int	try_beginning_group(
	t_lexer	**lex_cur, t_buffer *buffer)
{
	int	status;

	status = PARENTHESIS_BEGIN;
	while (status == PARENTHESIS_BEGIN)
	{
		status = try_parenthesis(lex_cur, buffer);
		if (status == PARENTHESIS_END)
		{
			return (set_err_and_msg((*lex_cur)->token_type,
					*lex_cur, buffer), SYNTAX_ERROR);
		}
		else if (status == SYNTAX_ERROR)
			return (SYNTAX_ERROR);
	}
	return (SUCCESS);
}

/**
 * parses a pottentially multitude of 
 * beginning parenthesis ')'
 * 
 * checks wrongly placed
 * beginning parenthesis syntax error:  ) ) ( (
 * among other syntax checks
*/
int	try_ending_group(
	t_lexer	**lex_cur, t_buffer *buffer)
{
	int	status;

	status = SUCCESS;
	while (status != NONE && status != EXIT)
	{
		status = try_parenthesis(lex_cur, buffer);
		if (status == PARENTHESIS_BEGIN)
			return (set_err_and_msg((*lex_cur)->token_type,
					*lex_cur, buffer), SYNTAX_ERROR);
		else if (status == SYNTAX_ERROR)
			return (SYNTAX_ERROR);
	}
	return (status);
}

int	decrement_all_cmd_cnts(t_buffer *buffer)
{
	int	i;
	int	decr_bool;

	decr_bool = NONE_DECREMENTED;
	i = 0;
	while (buffer->group_start_cmd[i] != NULL)
	{
		if (buffer->group_start_cmd[i]->parenthesis_cnt_personal > 0)
		{
			buffer->group_start_cmd[i]->parenthesis_cnt_personal--;
			decr_bool = DECREMENTED;
		}
		if (buffer->group_start_cmd[i]->parenthesis_cnt_personal == 0)
			buffer->group_start_cmd[i]->parenthesis_status = CLOSED;
		i++;
	}
	return (decr_bool);
}

void	increment_all_open_groups_cnt(t_buffer *buffer)
{
	int	i;

	i = 0;
	while (buffer->group_start_cmd[i] != NULL)
	{
		if (buffer->group_start_cmd[i]->parenthesis_status == OPEN)
		{
			buffer->group_start_cmd[i]->parenthesis_cnt_personal
				+= buffer->cmd_group_temp_cnt;
		}
		i++;
	}
}

void	increase_lenght_previous_groups(t_buffer *buffer)
{
	int	i;

	i = 0;
	while (buffer->group_start_cmd[i] != NULL)
	{
		if (buffer->group_start_cmd[i]->parenthesis_status == OPEN)
			buffer->group_start_cmd[i]->cmd_group_len++;
		i++;
	}
}
