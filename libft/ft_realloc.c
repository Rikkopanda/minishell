/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikverhoeven <rikverhoeven@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:01:33 by rverhoev          #+#    #+#             */
/*   Updated: 2024/04/21 16:07:51 by rikverhoeve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char	*new_ptr;

	if (!size && ptr)
	{
		free(ptr);
		ptr = 0;
		return (NULL);
	}
	else if (!size)
		return (NULL);
	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	new_ptr[0] = '\0';
	ft_strlcpy(new_ptr, ptr, size);
	free(ptr);
	ptr = 0;
	return ((void *)new_ptr);
}
