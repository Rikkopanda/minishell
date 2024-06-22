/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                      :+:         :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 12:43:33 by rverhoev          #+#    #+#             */
/*   Updated: 2023/10/15 12:43:34 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	build_str(char	**substr, char const *s, size_t	j, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && j < ft_strlen(s))
	{
		(*substr)[i] = s[j];
		i++;
		j++;
	}
	(*substr)[i] = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;

	if (start > ft_strlen(s) || len == 0)
	{
		substr = (char *)malloc(sizeof(char) * 1);
		substr[0] = '\0';
		return (substr);
	}
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	build_str(&substr, s, start, len);
	return (substr);
}

//int main()
//{
//	char *str = "hallo dit is ene test";
//	char *str2;

//	str2 = ft_substr("tripouille", 0, 42000);
//	//str2 = ft_substr(str, 6, 9);
//	printf("%s", str2);
//	free(str2);
//}