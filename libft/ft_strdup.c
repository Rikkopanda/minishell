/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                      :+:         :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 12:43:33 by rverhoev          #+#    #+#             */
/*   Updated: 2023/10/15 12:43:34 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * always returns malloced string
*/
char	*ft_strdup(const char *s)
{
	int		len;
	char	*new_str;
	char	*str;

	str = (char *)s;
	len = ft_strlen(str);
	new_str = (char *)malloc(sizeof(char) * len + 1);
	if (!new_str)
		return (NULL);
	if (len == 0)
	{
		new_str[0] = '\0';
		return (new_str);
	}
	ft_strcpy(new_str, str);
	return (new_str);
}
