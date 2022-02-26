/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:41:37 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/26 09:11:24 by zarachne         ###   ########.fr       */
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
		if (dup2(shell->fds[fd][1], STDOUT) == -1)
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
