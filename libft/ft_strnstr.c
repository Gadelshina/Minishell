/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 19:53:14 by zarachne          #+#    #+#             */
/*   Updated: 2021/11/27 19:53:16 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
* first occurrence of a substring needle in a string haystack. 
* search for haystack is limited to len number of characters. returns a pointer 
* for the found entry / or NULL. if needle is an empty string, returns haystack.
*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	search;
	unsigned int	i;

	search = 0;
	if (! *needle)
		return ((char *)haystack);
	while (haystack[search] && (size_t)search < len)
	{
		if (haystack[search] == needle[0])
		{
			i = 1;
			while (needle[i] != '\0' && haystack[search + i] == needle[i]
				&& (size_t)(search + i) < len)
				i++;
			if (needle[i] == '\0')
				return ((char *)&haystack[search]);
		}
		search++;
	}
	return (0);
}
