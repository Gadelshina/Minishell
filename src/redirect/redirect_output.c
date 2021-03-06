/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:44:08 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/25 12:36:36 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*get_prev_redirect(t_token *token)
{
	t_token	*tmp;

	tmp = token->prev;
	while (tmp && tmp->type != REDIR_OUT && tmp->type != REDIR_OUT_2)
		tmp = tmp->prev;
	return (tmp);
}

static void	prepare_output(t_main *shell, t_token *token)
{
	get_prev_redirect(token)->skip = TRUE;
	ft_close_fd(shell->fd_out);
}

int	redirect_output(t_main *shell, t_token *token, int *new_output)
{
	if (*new_output)
		prepare_output(shell, token);
	if (token->next)
	{
		if (token->type == REDIR_OUT)
			shell->fd_out = open(token->next->str, O_CREAT | O_WRONLY | \
				O_TRUNC, S_IRWXU);
		else if (token->type == REDIR_OUT_2)
			shell->fd_out = open(token->next->str, O_CREAT | O_WRONLY | \
				O_APPEND, S_IRWXU);
		if (shell->fd_out == -1)
			return (return_err(shell));
		else if (dup2(shell->fd_out, 1) == -1)
			return (return_err(shell));
		(*new_output) = 1;
	}
	else
		return (return_err(shell));
	return (0);
}
