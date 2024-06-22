/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:20:06 by rverhoev          #+#    #+#             */
/*   Updated: 2024/04/23 08:03:49 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper_functions.h"

t_cmd	*cmd_lstlast(t_cmd *lst)
{
	t_cmd	*current;

	if (lst == NULL)
		return (0);
	current = lst;
	while (current->next != NULL)
		current = current->next;
	return (current);
}

void	cmd_lstadd_back(t_cmd **lst, t_cmd *new)
{
	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
		cmd_lstlast(*lst)->next = new;
}

t_cmd	*cmd_lstnew(char **args, int token, t_buffer *buffer)
{
	t_cmd	*rtn;

	(void)args;
	rtn = (t_cmd *)malloc(sizeof(t_cmd));
	if (!rtn)
		clean_and_exit(MALLOC_ERROR, buffer);
	rtn->operator = token;
	rtn->in_lst = NULL;
	rtn->out_lst = NULL;
	rtn->arg_lst = NULL;
	rtn->next = NULL;
	rtn->parenthesis_status = NO_PARE;
	rtn->parenthesis_cnt_personal = 0;
	rtn->cmd_group_len = 0;
	return (rtn);
}

/*
	put lex_node in new redir variable,
	set old lex variable to lex_node->next.
	redir variable's node->next to NULL.
	handling as seperate lists, otherwise it also has all next links.
*/
void	lexnode_to_redir_lst(t_lexer **redir_lst, t_lexer **lex_cur)
{
	t_lexer	*tmp;

	if (*redir_lst == NULL)
	{
		tmp = *lex_cur;
		(*lex_cur) = (*lex_cur)->next;
		tmp->next = NULL;
		*redir_lst = tmp;
	}
	else
	{
		tmp = *lex_cur;
		(*lex_cur) = (*lex_cur)->next;
		tmp->next = NULL;
		lex_lstlast(*redir_lst)->next = tmp;
	}
}
