/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazrael <aazrael@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:13:13 by aazrael           #+#    #+#             */
/*   Updated: 2022/02/08 16:13:15 by aazrael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static unsigned int	ft_help(char const *s1, char *start, char *end)
{
	unsigned int	outstr_size;

	if (!*s1 || end == start)
		outstr_size = 2;
	else
		outstr_size = end - start + 2;
	return (outstr_size);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int				i;
	unsigned int	outstr_size;
	char			*start;
	char			*end;
	char			*res;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	i = 0;
	while (s1[i] && ft_set(s1[i], set))
		i++;
	start = (char *)&s1[i];
	i = ft_strlen(s1) - 1;
	if (i != -1)
		while (i >= 0 && ft_set(s1[i], set))
			i--;
	end = (char *)&s1[i];
	outstr_size = ft_help(s1, start, end);
	res = malloc(sizeof(char) * outstr_size);
	if (NULL == res)
		return (NULL);
	ft_strlcpy(res, start, outstr_size);
	return (res);
}
