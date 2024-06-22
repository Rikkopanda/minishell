/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:23:56 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/10 11:01:09 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	unbr_len(unsigned int n)
{
	size_t	i;

	i = 1;
	while (n / 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	ft_utoa_1000(unsigned int num, char str[1000])
{
	size_t				digits;
	int					digits_save;

	digits = unbr_len(num);
	digits_save = digits;
	(str)[digits] = '\0';
	while (digits--)
	{
		(str)[digits] = num % 10 + '0';
		num = num / 10;
	}
	return (digits_save);
}
