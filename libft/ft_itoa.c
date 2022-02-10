/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazrael <aazrael@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:14:37 by aazrael           #+#    #+#             */
/*   Updated: 2022/02/08 16:14:38 by aazrael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int long n)
{
	int			i;
	long int	ii;

	i = 1;
	ii = 10;
	while (i < 11)
	{
		if (n < ii)
			return (i);
		ii = ii * 10;
		i++;
	}
	return (1);
}

static int	ft_10_st(int r)
{
	unsigned int	n;

	n = 1;
	while (--r)
		n = n * 10;
	return (n);
}

static void	ft_help_f(char *res, int i, int neg, int long nl)
{
	int	r;

	r = ft_len(nl);
	while (i < r)
	{
		res[i + neg] = (nl / ft_10_st(r - i)) + 48;
		nl = nl % ft_10_st(r - i);
		i++;
	}
	res[i + neg] = '\0';
}

char	*ft_itoa(int n)
{
	size_t		r;
	int			neg;
	char		*res;
	int long	nl;
	int			i;

	nl = (int long)n;
	neg = 0;
	if (nl < 0)
	{
		neg = 1;
		nl = nl * -1;
	}
	r = ft_len(nl);
	res = (char *) malloc(sizeof(char) * (r + neg + 1));
	if (NULL == res)
		return (NULL);
	i = 0;
	if (neg)
		res[0] = '-';
	ft_help_f(res, i, neg, nl);
	return (res);
}
