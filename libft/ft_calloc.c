/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 19:50:21 by zarachne          #+#    #+#             */
/*   Updated: 2021/11/27 19:50:23 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{	
	size_t	i;
	char	*p;

	i = 0;
	p = malloc(size * count);
	if (p != NULL)
		ft_memset(p, 0, (size * count));
	return (p);
}
