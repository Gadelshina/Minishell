/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 08:36:19 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/26 09:13:09 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_new_in(t_main *shell, t_token *token)
{
	ft_close_fd(shell->fd_in);
	if (token->next->type == CMD || token->next->type == ARG)
	{
		shell->fd_in = open(token->next->str, O_RDONLY, S_IRWXU);
		if (shell->fd_in == -1)
			return (shell_err(shell));
		else if (dup2(shell->fd_in, 0) == -1)
			return (shell_err(shell));
	}
}

static void	handle_new_out(t_main *shell, t_token *token)
{
	char	*file;

	ft_close_fd(shell->fd_out);
	if (token->next->type == ARG || token->next->type == CMD)
	{
		file = token->next->str;
		if (token->type == REDIR_OUT)
			shell->fd_out = open(file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		if (token->type == REDIR_OUT_2)
			shell->fd_out = open(file, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
		if (shell->error)
			return (shell_err(shell));
		else if (dup2(shell->fd_out, 1) == -1)
			return (shell_err(shell));
	}
}

static void	handle_new_heredoc(t_main *shell, t_token *token)
{
	ft_close_fd(shell->fd_in);
	if (token->next->type == ARG || token->next->type == CMD)
		execute_heredoc(shell, token);
}

int	token_has_redir_in(t_main *shell, t_token *token)
{
	t_token	*desire;
	int		ret;

	ret = 0;
	desire = token;
	while (desire->prev && desire->prev->type != PIPE)
		desire = desire->prev;
	while (desire && desire->type != PIPE)
	{
		if (desire->type == REDIR_IN)
		{
			handle_new_in(shell, desire);
			ret = 1;
		}
		if (desire->type == REDIR_HEREDOC)
		{
			handle_new_heredoc(shell, desire);
			ret = 1;
		}
		desire = desire->next;
	}
	if (shell->error)
		return (0);
	return (ret);
}

int	token_has_redir_out(t_main *shell, t_token *token)
{
	t_token	*desire;
	int		ret;

	ret = 0;
	desire = token;
	while (desire->prev && desire->prev->type != PIPE)
		desire = desire->prev;
	while (desire && desire->type != PIPE)
	{
		if (desire->type == REDIR_OUT || desire->type == REDIR_OUT_2)
		{
			ret = 1;
			handle_new_out(shell, desire);
		}
		desire = desire->next;
	}
	if (shell->error)
		return (0);
	return (ret);
}
