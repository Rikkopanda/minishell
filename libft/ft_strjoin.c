/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_v2.c                                     :+:         :+:    :+*/
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 12:43:33 by rverhoev          #+#    #+#             */
/*   Updated: 2023/10/15 12:43:34 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	build_str(char **strjoined, char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (s1[i])
	{
		(*strjoined)[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		(*strjoined)[j + i] = s2[j];
		j++;
	}
	(*strjoined)[j + i] = '\0';
}

/**
 * if s1 is NULL, builds new copy of s2 and returns it
 * otherwise if both exists, s2 concatenates on s1
*/
char	*ft_strjoin_v2(char const *s1, char const *s2)
{
	char			*strjoined;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	strjoined = (char *)malloc(sizeof(char)
			* (ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1));
	if (strjoined == NULL)
		return (NULL);
	build_str(&strjoined, s1, s2);
	return (strjoined);
}
//int main()
//{
//	char str1[] = "test";
//	char str2[] = "123";
//	char *str3;
//	str3 = ft_strjoin_v2(str1, str2);
//	printf("%s", str3);
//	free(str3);
//}