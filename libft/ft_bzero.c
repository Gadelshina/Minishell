/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazrael <aazrael@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:15:03 by aazrael           #+#    #+#             */
/*   Updated: 2022/02/08 16:15:05 by aazrael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*x;

	x = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		*x++ = '\0';
		i++;
	}
}
