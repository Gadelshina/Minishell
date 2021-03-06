/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:15:07 by aazrael           #+#    #+#             */
/*   Updated: 2022/02/24 18:19:26 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == '\n' || c == '\f' || c == '\t' || c == '\v' || \
		c == ' ' || c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int long	res;
	int			i;
	int			sign;

	i = 0;
	res = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((res > 922337203685477580 || (res == 922337203685477580 && \
		(str[i] - '0') > 7)) && sign == 1)
			return (-1);
		else if ((res > 922337203685477580 || (res == 922337203685477580 && \
			(str[i] - '0') > 8)) && sign == -1)
			return (0);
		res = res * 10 + (str[i++] - '0');
	}
	return ((int)res * sign);
}
