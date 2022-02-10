/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 19:51:38 by zarachne          #+#    #+#             */
/*   Updated: 2021/11/27 19:51:40 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
* Copies n byte from src to dest. memory areas should not overlap(ub).
*/
void	*ft_memcpy(void *dst1, const void *src1, size_t n)
{
	char	*dst;
	char	*src;

	if (n == 0 || dst1 == src1)
		return (dst1);
	dst = (char *)dst1;
	src = (char *)src1;
	while (n--)
		*dst++ = *src++;
	return (dst1);
}
