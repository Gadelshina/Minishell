/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazrael <aazrael@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:41:37 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/25 10:38:27 by aazrael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_child(void)
{
	free_env();
	exit (1);
}

void	set_fd_first(t_main *shell, t_token *token, int fd)
{
	token_has_redir_in(shell, token);
	if (!token_has_redir_out(shell, token))
		if (dup2(shell->fds[fd][1], 1) == -1)
			return (shell_err(shell));
	ft_close_fd(shell->fds[fd][0]);
}

void	set_fd_last(t_main *shell, t_token *token, int fd)
{
	if (!token_has_redir_in(shell, token))
	{
		if (dup2(shell->fds[fd][0], 0) == -1)
			shell_err(shell);
		ft_close_fd(shell->fds[fd][1]);
	}
	token_has_redir_out(shell, token);
}
