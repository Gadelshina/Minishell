/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazrael <aazrael@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:14:31 by aazrael           #+#    #+#             */
/*   Updated: 2022/02/08 16:14:35 by aazrael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, \
		size_t n)
{
	unsigned char	*x;
	unsigned char	*y;
	unsigned char	ucc;
	size_t			i;

	ucc = (unsigned char)c;
	i = 0;
	x = (unsigned char *)dst;
	y = (unsigned char *)src;
	if (dst == 0 && src == 0)
		return (dst);
	while (n--)
	{
		x[i] = y[i];
		if (y[i] == ucc)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
