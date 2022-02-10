/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazrael <aazrael@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:13:53 by aazrael           #+#    #+#             */
/*   Updated: 2022/02/08 16:13:55 by aazrael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_numbers_str(char const *s, char c)
{
	size_t			i;
	unsigned int	n;

	i = 1;
	n = 0;
	while (s[i])
	{
		if ((s[i] == c) && (s[i - 1] != c))
			n++;
		i++;
	}
	if (s[i - 1] != c)
		n++;
	return (n);
}

static void	ft_free(char **s, unsigned int n)
{
	while (n)
	{
		free (s[n]);
		n--;
	}
	free (s);
}

static char	*ft_sub(const char *s, char c, int pos)
{
	unsigned int	i;
	char			*ret;

	i = pos;
	while (s[i])
	{
		if (s[i] == c)
		{
			ret = ft_substr(s, pos, (i - pos));
			return (ret);
		}
		i++;
	}
	ret = ft_substr(s, pos, (i - pos));
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char			**res;
	unsigned int	i;
	unsigned int	pos;

	i = 0;
	pos = 0;
	res = (char **)malloc(sizeof(char *) * (ft_numbers_str(s, c) + 1));
	if (NULL == res)
		return (NULL);
	while (s[pos] && i < ft_numbers_str(s, c))
	{
		if (s[pos] != c)
		{
			res[i] = ft_sub(s, c, pos);
			pos = pos + ft_strlen(res[i]);
			if (NULL == res[i])
				ft_free(res, i);
			i++;
		}
		pos++;
	}
	res[i] = NULL;
	return (res);
}
