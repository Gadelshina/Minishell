/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 09:04:30 by aazrael           #+#    #+#             */
/*   Updated: 2022/02/25 22:41:44 by zarachne         ###   ########.fr       */
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

int	return_err(t_main *shell)
{
	shell->error = TRUE;
	g_main.g_return = 1;
	perror("minishell");
	return (1);
}

int	fatal_err(t_main *shell)
{
	if (shell-> error)
		return (1);
	if (g_main.g_run == FALSE)
		return (1);
	return (0);
}
