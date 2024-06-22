/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:11:40 by rikverhoeve       #+#    #+#             */
/*   Updated: 2024/04/21 15:57:55 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	linked_list_size(t_quotes_part *node)
{
	int	size;

	if (node == NULL)
		return (0);
	size = 1;
	while (node != NULL)
	{
		node = node->next;
		size++;
	}
	return (size);
}
// printf("_______________\n");
// printf("%p, %s\n", node, node->part);
// printf("_______________\n");

t_quotes_part	*swap(t_quotes_part *p1, t_quotes_part *p2)
{
	t_quotes_part	*tmp;

	tmp = p2->next;
	p2->next = p1;
	p1->next = tmp;
	return (p2);
}

#define A_IS_SMALLER 0
#define A_IS_BIGGER 1

int	alpha_compare(unsigned char value_A, unsigned char value_B)
{
	if ((value_A >= 'A' && value_A <= 'Z')
		&& (value_B >= 'a' && value_B <= 'z'))
	{
		value_A += 32;
		if (value_A == value_B)
			return (A_IS_SMALLER);
	}
	else if ((value_A >= 'a' && value_A <= 'z')
		&& (value_B >= 'A' && value_B <= 'Z'))
	{
		value_B += 32;
		if (value_A == value_B)
			return (A_IS_BIGGER);
	}
	if (value_A > value_B)
		return (A_IS_BIGGER);
	else
		return (A_IS_SMALLER);
}

/**
 * Bubble sort:
 * moves head_placeholder along the list (size - 2) amount of times
 * swap if neccecary
 * reset head_placehodler to actual list head and repeat process
*/
void	sort_linked_list_alphabetical(t_quotes_part **content_list,
	int i, int j, const int size)
{
	t_quotes_part	**head_placeholder;
	t_quotes_part	*p1;
	t_quotes_part	*p2;

	i = 0;
	while (i < size - 1)
	{
		head_placeholder = content_list;
		j = 0;
		while (j < size - 2)
		{
			if (alpha_compare((*head_placeholder)->part[0],
					(*head_placeholder)->next->part[0]) == A_IS_BIGGER)
			{
				p1 = *head_placeholder;
				p2 = p1->next;
				*head_placeholder = swap(p1, p2);
			}
			j++;
			head_placeholder = &(*head_placeholder)->next;
		}
		i++;
	}
}
// printf("p1 = %p, %s\n", p1, p1->part);
// printf("p2 = %p, %s\n", p2, p2->part);