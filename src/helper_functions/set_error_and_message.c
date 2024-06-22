/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_err_and_msg.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:51:48 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/19 15:52:33 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper_functions.h"

void	try_set_message1(char	**message, int type,
	t_buffer *buffer)
{
	if (type == IN)
		*message = ft_strdup("<");
	else if (type == OUT)
		*message = ft_strdup(">");
	else if (type == HEREDOC)
		*message = ft_strdup("<<");
	else if (type == AND_OPERATOR)
		*message = ft_strdup("&&");
	else if (type == OR_OPERATOR)
		*message = ft_strdup("||");
	else if (type == PIPE)
		*message = ft_strdup("|");
	else if (type == APPEND)
		*message = ft_strdup(">>");
	else
		return ;
	if (!*message)
		clean_and_exit(MALLOC_ERROR, buffer);
}

void	try_set_message2(char	**message, int type,
	t_lexer *lex, t_buffer *buffer)
{
	if (*message != NULL)
		return ;
	if (type == NEW_LINE)
		*message = ft_strdup("newline");
	else if (type == (t_token_type)SINGLE_QUOTE)
		*message = ft_strdup("'");
	else if (type == (t_token_type)DOUBLE_QUOTE)
		*message = ft_strdup("\"");
	else if (type == PARENTHESIS_BEGIN)
		*message = ft_strdup("(");
	else if (type == PARENTHESIS_END)
		*message = ft_strdup(")");
	else if (type == WORD)
		*message = ft_strdup(lex->word);
	else
		return ;
	if (!*message)
		clean_and_exit(MALLOC_ERROR, buffer);
}

void	set_err_and_msg(int type, t_lexer *lex, t_buffer *buffer)
{
	char	*message;

	buffer->exit_status = SYNTAX_ERROR;
	message = NULL;
	try_set_message1(&message, type, buffer);
	try_set_message2(&message, type, lex, buffer);
	if (message != NULL)
	{
		ft_putstr_fd("minishell: syntax error near '", 2);
		ft_putstr_fd(message, 2);
		ft_putstr_fd("'\n", 2);
		free(message);
	}
	else
		ft_putstr_fd("minishell: syntax error\n", 2);
}
