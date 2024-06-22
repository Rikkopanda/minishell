/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 10:43:00 by rverhoev          #+#    #+#             */
/*   Updated: 2024/02/24 14:48:06 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static int	check_args(char *base)
{
	int	len;
	int	j;

	len = ft_strlen(base);
	j = len;
	if (len <= 1)
		return (1);
	while (0 <= len)
	{
		while (0 <= j)
		{
			if (j != len)
			{
				if (base[len] == base[j])
					return (1);
			}
			if (base[len] == '+' || base[len] == '-')
				return (1);
			j--;
		}
		len--;
		j = len + 1;
	}
	return (0);
}

int	ft_putnbr_base_loop(char *array, int nbr, char *base)
{
	int	i;
	int	rest;
	int	base_length;

	base_length = ft_strlen(base);
	i = 0;
	while (nbr >= base_length || (nbr < 0 && nbr <= (base_length * -1)))
	{
		if (nbr < 0)
			rest = -1 * (nbr % (-1 * base_length));
		else
			rest = nbr % base_length;
		nbr = nbr / base_length;
		if (nbr < 0)
			nbr = nbr * -1;
		array[i] = base[rest];
		i++;
	}
	if (nbr <= base_length)
		array[i] = base[nbr];
	return (i);
}
//omdat -2147483648 * -1 overflow is,
//doe je eerst modulo(maakt positieve rest,
//als negatief is-> Dan nbr/10, dan nbr * -1 is mogelijk.
//daarna blijft het positief. In het begin was "-" al geprint.

void	ft_putnbr_base(int nbr, char *base)
{
	int		i;
	char	array[130];

	if (check_args(base))
		return ;
	if (nbr < 0)
		write(1, "-", 1);
	i = ft_putnbr_base_loop(array, nbr, base);
	while (i >= 0)
	{
		write(1, &array[i], 1);
		i--;
	}
}
// 					i			0		1	2	3
// 					nbr			22		11	5	2
// 					rest		0		1	1	0
// -\0 len			baselen		2		2	2	2
// 					array		0		1	1	0
// 					newnum		11		5	2	0
//					while		x		1	0	0
// array[int_length] = '\0';
// base string
// int arr
// rest = nr % baselen
// nr = nr / len
// arr[x++]	= base[rest] (rest is int getal kleiner dan basemax)
// int	main(void)
// {
// 	int test;
// 	char base[] = "01";
// 	test = 2147483647;
// 	//test = 2147483647;
// 	ft_putnbr_base(test, base);
// 	//ft_putnbr_base(test, hex);
// }