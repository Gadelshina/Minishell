/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazrael <aazrael@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:13:39 by aazrael           #+#    #+#             */
/*   Updated: 2022/02/08 16:13:41 by aazrael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_min(size_t a, size_t b)
{
	if (a <= b)
		return (a);
	return (b);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_size;
	size_t	result_size;

	dst_size = ft_strlen(dst);
	result_size = ft_min(size, dst_size) + ft_strlen(src);
	if (!(size <= dst_size))
	{
		dst = dst + dst_size;
		size = size - dst_size;
		while (*src && (size-- > 1))
			*dst++ = *src++;
		*dst = '\0';
	}
	return (result_size);
}
