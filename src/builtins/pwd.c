/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazrael <aazrael@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:59:37 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/25 10:30:20 by aazrael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (str)
	{
		ft_putendl_fd(str, 1);
		free(str);
	}
	else
		return (1);
	return (0);
}
