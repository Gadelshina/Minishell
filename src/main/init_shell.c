/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:35:54 by aazrael           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/02/15 14:48:40 by aazrael          ###   ########.fr       */
=======
/*   Updated: 2022/02/21 11:29:53 by zarachne         ###   ########.fr       */
>>>>>>> f3928be60c8e60c64b13df370444bd41755ebc06
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
