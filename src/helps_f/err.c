/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazrael <aazrael@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 09:04:30 by aazrael           #+#    #+#             */
/*   Updated: 2022/02/09 16:31:04 by aazrael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_err(void)
{
	ft_putendl_fd("Malloc error", 2);
	exit(EXIT_FAILURE);
}

void	shell_err(t_main *shell)
{
	shell->error = TRUE;
	g_main.g_return = 1;
	perror("minishell: an error has occured");
	return ;
}
