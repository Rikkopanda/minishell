/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uint_atoi_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 10:43:00 by rverhoev          #+#    #+#             */
/*   Updated: 2024/04/21 16:18:36 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>
// #include <stdio.h>
#include <stdio.h>

int	start_initial_substring(char *str, char *base, int passeer)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		j = 0;
		count = 0;
		while (base[j] != '\0')
		{
			if (str[i] == base[j])
				count = 1;
			j++;
		}
		if (!count)
			break ;
		i++;
	}
	str[i] = '\0';
	return (passeer);
}
//makes a new string(puts \0 at end) of foundend numbers (correct number base)

static int	ft_atoi2(char *str, char *base, int *min)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	*min = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ' && min == 0)
			i++;
		if (str[i] == '-')
			*min = *min + 1;
		while (base[j] != '\0')
		{
			if (str[i] == base[j])
				return (start_initial_substring(&str[i], base, i));
			j++;
		}
		if (!(str[i] == '-' || (str[i] == '+')) && *min > 0)
			return (-1);
		j = 0;
		i++;
	}
	return (-1);
}
//changes i to index of point starting the initial string. 
//initial string contains only correct base numbers,
//because start_initial_sub puts a \0 when it sees other characters
//atoi, first ' ' chars allowed, counts '-', if not '+' '-' or base char,
//after ' ' chars = return 0;
//in atoi_base if ft_atoi = 0, then is dec_nbr = 0
//NO it would then when i = 0 in atoi_base,
//make dec_nbr 0. BUT also when base_nbr actually-
//-starts at i = 0(start) also make nbr 0

unsigned int	base_substr_to_int(char *base, char *str, int i, int base_len)
{
	int				j;
	int				str_len;
	unsigned int	dec_nbr;

	dec_nbr = 0;
	j = 0;
	str_len = 0;
	while (str[str_len] != '\0')
		str_len++;
	str_len--;
	while (i <= str_len)
	{
		j = 0;
		while (j <= base_len)
		{
			if (str[i] == base[j])
				dec_nbr = dec_nbr * base_len + j;
			j++;
		}
		i++;
	}
	return (dec_nbr);
}

static int	check_args(char *base, int len)
{
	int	j;

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

size_t	ft_uint_atoi_base(char *str, char *base)
{
	int				base_len;
	unsigned int	dec_nbr;
	int				min;
	int				i;

	i = ft_atoi2(str, base, &min);
	dec_nbr = 0;
	base_len = 0;
	while (base[base_len] != '\0')
		base_len++;
	if (check_args(base, base_len))
		return (0);
	if (i == -1)
		return (0);
	dec_nbr = base_substr_to_int(base, str, i, base_len);
	return (dec_nbr);
}
//ft_atoi changes i to start, 
//gives str after start(i) terminator at end if hits non-base
//--
//base_subsr_to_int converts given str(with start i), 
//which is the base_nbr_str, to int
// int	main(void)
// {
// 	char test[] = "-80000000";
// 	char test1[] = "-10000000000000000000000000000000";
// 	char hex[] = "0123456789ABCDEF";
// 	printf("%d", ft_atoi_base(test1, "01"));
// }