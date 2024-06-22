/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:50:48 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/26 11:57:54 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

static void	print_cmd_p1(t_cmd *cmd_cur)
{
	t_lexer	*cmd_cur_arg;
	t_lexer	*current_out;

	dprintf(2, "CMD:\targs=[");
	cmd_cur_arg = cmd_cur->arg_lst;
	while (cmd_cur_arg != NULL)
	{
		dprintf(2, "{%s}", cmd_cur_arg->word);
		cmd_cur_arg = cmd_cur_arg->next;
	}
	dprintf(2, "]");
	dprintf(2, "\tout lst=[");
	current_out = cmd_cur->out_lst;
	while (current_out != NULL)
	{
		dprintf(2, "{%s", current_out->word);
		print_lex(current_out);
		dprintf(2, "}");
		current_out = current_out->next;
	}
	dprintf(2, "]");
	dprintf(2, "\tin lst=[");
}

static void	print_cmd_p2(t_cmd *cmd_cur)
{
	t_lexer	*current_in;

	current_in = cmd_cur->in_lst;
	while (current_in != NULL)
	{
		dprintf(2, "{%s", current_in->word);
		print_lex(current_in);
		dprintf(2, "}");
		current_in = current_in->next;
	}
	dprintf(2, "]\tPRE_OPERATOR_TYPE=[");
	if (cmd_cur->operator == AND_OPERATOR)
		dprintf(2, "AND");
	else if (cmd_cur->operator == OR_OPERATOR)
		dprintf(2, "OR");
	else if (cmd_cur->operator == PIPE)
		dprintf(2, "PIPE");
	else
		dprintf(2, "NONE");
}

void	print_cmd_lst(t_cmd *cmd_lst)
{
	t_cmd		*cmd_cur;

	cmd_cur = cmd_lst;
	while (cmd_cur != NULL)
	{
		if (cmd_cur == NULL)
			return ;
		print_cmd_p1(cmd_cur);
		print_cmd_p2(cmd_cur);
		dprintf(2, "]\tLENGHT_OF_CMD_GROUP=[%d]", cmd_cur->cmd_group_len);
		if (cmd_cur->parenthesis_status == OPEN)
			dprintf(2, "\tPARENTHESIS_STATUS= OPEN");
		else if (cmd_cur->parenthesis_status == CLOSED)
			dprintf(2, "\tPARENTHESIS_STATUS= CLOSED");
		else
			dprintf(2, "\tPARENTHESIS_STATUS= NONE");
		dprintf(2, "\tbuiltin=[%p]\n", cmd_cur->builtin);
		cmd_cur = cmd_cur->next;
	}
}
