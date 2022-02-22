/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazrael <aazrael@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:35:54 by aazrael           #+#    #+#             */
/*   Updated: 2022/02/22 21:49:46 by aazrael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init0_shell(t_main *shell, char ***arr)
{
	*arr = NULL;
	*arr = __environ;
	__environ = malloc_env();
	shell->exit = FALSE;
	g_main.g_return = 0;
	g_main.g_run = FALSE;
}

void	init1_shell(t_main *shell)
{
	shell->message = ft_strdup("$$:");
	shell->exit = FALSE;
	shell->in = dup(STDIN);
	if (!shell->in)
		return (shell_err(shell));
	shell->out = dup(STDOUT);
	if (!shell->out)
		return (shell_err(shell));
	shell->fd_in = -1;
	shell->fd_out = -1;
	shell->childs = NULL;
	shell->error = FALSE;
	g_main.g_here_doc = FALSE;
}
