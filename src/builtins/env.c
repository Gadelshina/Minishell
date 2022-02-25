/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazrael <aazrael@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:56:28 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/25 10:35:45 by aazrael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(void)
{
	int	i;

	i = 0;
	while (__environ[i])
	{
		if (ft_strchr(__environ[i], '='))
			printf("%s\n", __environ[i]);
		i++;
	}
	return (0);
}
