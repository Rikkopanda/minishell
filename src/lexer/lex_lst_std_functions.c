/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_lst_std_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:15:34 by rverhoev          #+#    #+#             */
/*   Updated: 2024/04/29 18:42:50 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	*lex_lstlast(t_lexer *lst)
{
	t_lexer	*current;

	if (lst == NULL)
		return (0);
	current = lst;
	while (current->next != NULL)
		current = current->next;
	return (current);
}

void	lex_lstadd_back(t_lexer **lst, t_lexer *new)
{
	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
		lex_lstlast(*lst)->next = new;
}

t_lexer	*lex_lstnew(char *word, int token, t_buffer *buffer)
{
	t_lexer	*rtn;

	rtn = (t_lexer *)malloc(sizeof(t_lexer));
	if (!rtn)
		clean_and_exit(MALLOC_ERROR, buffer);
	rtn->word = word;
	rtn->token_type = token;
	rtn->next = NULL;
	rtn->dynamic_joining = FALSE;
	rtn->extra_space_if_new_strpart = FALSE;
	return (rtn);
}

t_lexer	**save_lex_ptrs(t_lexer *lexer, t_buffer *buffer)
{
	int			i;
	int			size;
	t_lexer		*cur_lex;
	t_lexer		**lex_ptrs;

	size = lex_size(lexer);
	lex_ptrs = malloc(sizeof(t_lexer *) * (size + 2));
	if (!lex_ptrs)
		clean_and_exit(MALLOC_ERROR, buffer);
	cur_lex = lexer;
	i = 0;
	while (i < size)
	{
		lex_ptrs[i] = cur_lex;
		cur_lex = cur_lex->next;
		i++;
		if (cur_lex == NULL)
			break ;
	}
	lex_ptrs[i] = NULL;
	return (lex_ptrs);
}
