/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:18:03 by rverhoev          #+#    #+#             */
/*   Updated: 2024/04/20 10:29:03 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	tokens_p1(char *line, int	*i, t_buffer *buffer)
{
	if (ft_strncmp(&line[*i], "<<", 2) == 0)
	{
		lex_lstadd_back(&buffer->lexer_list, lex_lstnew(NULL, HEREDOC, buffer));
		*i += 2;
	}
	else if (ft_strncmp(&line[*i], ">>", 2) == 0)
	{
		lex_lstadd_back(&buffer->lexer_list, lex_lstnew(NULL, APPEND, buffer));
		*i += 2;
	}
	else if (ft_strncmp(&line[*i], "&&", 2) == 0)
	{
		lex_lstadd_back(&buffer->lexer_list,
			lex_lstnew(NULL, AND_OPERATOR, buffer));
		*i += 2;
	}
	else if (line[*i] == '(')
	{
		lex_lstadd_back(&buffer->lexer_list,
			lex_lstnew(NULL, PARENTHESIS_BEGIN, buffer));
		(*i)++;
	}
	else
		return (FALSE);
	return (TRUE);
}

static int	tokens_p2(char *line, int	*i, t_buffer *buffer)
{
	if (line[*i] == ')')
	{
		lex_lstadd_back(&buffer->lexer_list,
			lex_lstnew(NULL, PARENTHESIS_END, buffer));
		(*i)++;
	}
	else if (ft_strncmp(&line[*i], "||", 2) == 0)
	{
		lex_lstadd_back(&buffer->lexer_list,
			lex_lstnew(NULL, OR_OPERATOR, buffer));
		*i += 2;
	}
	else if (line[*i] == '<')
	{
		lex_lstadd_back(&buffer->lexer_list, lex_lstnew(NULL, IN, buffer));
		(*i)++;
	}
	else
		return (FALSE);
	return (TRUE);
}

static int	tokens_p3(char *line, int	*i, t_buffer *buffer)
{
	if (line[*i] == '>')
	{
		lex_lstadd_back(&buffer->lexer_list, lex_lstnew(NULL, OUT, buffer));
		(*i)++;
	}
	else if (line[*i] == '|')
	{
		lex_lstadd_back(&buffer->lexer_list, lex_lstnew(NULL, PIPE, buffer));
		(*i)++;
	}
	else
		return (FALSE);
	return (TRUE);
}

void	try_tokens(char *line, int	*i, t_buffer *buffer)
{
	if (tokens_p1(line, i, buffer) == TRUE)
		return ;
	if (tokens_p2(line, i, buffer) == TRUE)
		return ;
	tokens_p3(line, i, buffer);
}
