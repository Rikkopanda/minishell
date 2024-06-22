/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:25:45 by rverhoev          #+#    #+#             */
/*   Updated: 2023/11/14 18:16:03 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_i_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

int	convert_to_nbr_str(char *nbr_str, unsigned int num
	, char *base_str, int who_invokes)
{
	static int	static_index;

	if (who_invokes == 0)
		static_index = 0;
	if (num >= ft_i_strlen(base_str))
	{
		convert_to_nbr_str(nbr_str, num / ft_i_strlen(base_str), base_str, 1);
		convert_to_nbr_str(nbr_str, num % ft_i_strlen(base_str), base_str, 1);
	}
	if (num < ft_i_strlen(base_str))
	{
		nbr_str[static_index] = base_str[num];
		static_index++;
	}
	return (ft_i_strlen(nbr_str));
}

//printf("\nstatic nbr = %d\n", static_index);
//printf("\nstr = %s\n", base_str);

int	int_case(int *len, va_list args)
{
	int	num;

	num = va_arg(args, int);
	if (num == INT_MIN)
		return ((*len)++, write(1, "-", 1), -2147483648);
	else if (num < 0)
	{
		write(1, "-", 1);
		(*len)++;
		num = num * -1;
	}
	return (num);
}

int	f_nbrbase(va_list args, char *nbrbase)
{
	char			*nbr_str;
	long long int	num;
	int				len;

	len = 0;
	nbr_str = (char *)ft_calloc(sizeof(char), 12);
	if (nbr_str == NULL)
		return (0);
	if (!strcmp("0123456789", nbrbase))
		num = int_case(&len, args);
	else
		num = va_arg(args, unsigned int);
	len += convert_to_nbr_str(nbr_str, num, nbrbase, 0);
	ft_putstr(nbr_str);
	free (nbr_str);
	nbr_str = 0;
	return (len);
}
