/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   try_word_parsing.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rikverhoeven <rikverhoeven@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/18 13:24:48 by rverhoev      #+#    #+#                 */
/*   Updated: 2024/04/29 16:52:32 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	build_no_ending_quote_part(t_try_quotes_tools	*tools,
	t_quotes_part	**str_part_lst, t_buffer *buffer)
{
	tools->new_str = ft_substr(tools->line,
			(tools->start - 1), (*(tools->i_ptr)) - (tools->start - 1));
	if (!tools->new_str)
		clean_and_exit(MALLOC_ERROR, buffer);
	strpart_lstadd_back(str_part_lst,
		strpart_lstnew(tools->new_str, NOQUOTES, buffer));
	return (SUCCESS);
}

int	try_quotes_str(char *line, int	*i,
		t_quotes_part	**str_part_lst, t_buffer *buffer)
{
	t_try_quotes_tools	tools;

	(*i)++;
	init_try_quotes_tools(&tools, line, *i - 1, i);
	while (line[*i] != tools.begin_quote)
	{
		if (line[*i] == '\0')
			return (build_no_ending_quote_part(&tools, str_part_lst, buffer));
		(*i)++;
	}
	tools.len = (*i) - tools.start;
	(*i)++;
	if (tools.len == 0)
		return (SUCCESS);
	tools.new_str = ft_substr(line, tools.start, tools.len);
	if (!tools.new_str)
		clean_and_exit(MALLOC_ERROR, buffer);
	strpart_lstadd_back(str_part_lst,
		strpart_lstnew(tools.new_str, tools.begin_quote, buffer));
	return (SUCCESS);
}
// printf("new str quotes %s\n", tools.new_str);

int	check_if_continue_noquotes(char *line, int *i)
{
	if (line[*i] == '\0')
		return (FALSE);
	else if (line[*i] == '$' && line[*i + 1] == ' ')
		return (TRUE);
	else if (ft_strchr(" <>|()\t", line[*i]) != NULL)
		return (FALSE);
	else if (line[*i] == SINGLE_QUOTE
		|| line[*i] == DOUBLE_QUOTE)
		return (FALSE);
	else if (line[*i] == '\0'
		|| ft_strncmp(&line[*i], "&&", 2) == 0)
		return (FALSE);
	return (TRUE);
}

int	try_noquotes_str(char *line, int *i,
	t_quotes_part **str_part_lst, t_buffer *buffer)
{
	int		start;
	int		len;
	char	*new_str;

	start = *i;
	while (check_if_continue_noquotes(line, i) == TRUE)
		(*i)++;
	len = *i - start;
	if (len != 0)
	{
		new_str = ft_substr(line, start, len);
		if (!new_str)
			clean_and_exit(MALLOC_ERROR, buffer);
		strpart_lstadd_back(str_part_lst,
			strpart_lstnew(new_str, NOQUOTES, buffer));
	}
	return (SUCCESS);
}
// printf("line %s, i %d, start %d, len %d\n", line, *i, start, len);
// printf("new %s\n", new_str);

/**
 * resetting last_lex->dynamic_joining to FALSE 
 * when done. so next round may make fresh
 * new lexes(instead of concating strpart to last lex)
 * 
 * joining of strpart to last lex expanded lex:
 * check_last_lex_node_if_came_from_env()  strpart comes from new try_quotes
 * dynamicly
 * 
 * 
 * last_strpart_shifted_for_env_expanded()  strpart comes from old try_quotes
 * joins after parsing, staticly
*/
void	try_word(int *start, char *line, int	*i, t_buffer *buffer)
{
	t_quotes_part	*str_part_lst;

	str_part_lst = NULL;
	while (line[*i] != '\0' && check_to_continue(line, i))
	{
		if (line[*i] == SINGLE_QUOTE || line[*i] == DOUBLE_QUOTE)
			try_quotes_str(line, i, &str_part_lst, buffer);
		else
			try_noquotes_str(line, i, &str_part_lst, buffer);
		if (check_dynamic_join_last_part(str_part_lst, line, i, buffer))
			join_latest_str_part_to_last_lex(str_part_lst, buffer);
		try_expander(&str_part_lst, buffer, &line[*i]);
		if (check_dynamic_join_post_expansion(str_part_lst, buffer))
			join_latest_str_part_to_last_lex(str_part_lst, buffer);
	}
	post_joining_and_clearing_parts(start, i, str_part_lst, buffer);
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}
// print_strparts(str_part_lst);
// printf("pre expander %s\n", strpart_lstlast(str_part_lst)->part);
// printf("post expander %s\n", strpart_lstlast(str_part_lst)->part);
// print_lex(buffer->lexer_list);
// print_lex(buffer->lexer_list);
// printf("0\n_____________________\n");
// print_lex(buffer->lexer_list);
// printf("_____________________\n");
// printf("_____________________\n");
