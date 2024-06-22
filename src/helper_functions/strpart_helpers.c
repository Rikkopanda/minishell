/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strpart_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:01:33 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/23 08:03:42 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper_functions.h"

t_quotes_part	*strpart_lstnew(char *str, int quote_type, t_buffer *buffer)
{
	t_quotes_part	*rtn;

	rtn = (t_quotes_part *)malloc(sizeof(t_quotes_part));
	if (!rtn)
		clean_and_exit(MALLOC_ERROR, buffer);
	rtn->part = str;
	rtn->type = quote_type;
	rtn->next = NULL;
	rtn->shifted_due_to_env_lex_expand = FALSE;
	rtn->built_expanded_into_latest_strpart = FALSE;
	return (rtn);
}

t_quotes_part	*strpart_lstlast(t_quotes_part *lst)
{
	t_quotes_part	*current;

	if (lst == NULL)
		return (NULL);
	current = lst;
	while (current->next != NULL)
		current = current->next;
	return (current);
}

void	strpart_lstadd_back(t_quotes_part **lst, t_quotes_part *new)
{
	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
		strpart_lstlast(*lst)->next = new;
}

int	strpart_lst_size(t_quotes_part *node)
{
	int	i;

	i = 0;
	while (node != NULL)
	{
		node = node->next;
		i++;
	}
	return (i);
}
