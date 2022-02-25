/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:03:54 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/25 09:39:29 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_error(t_main *shell)
{
	if (shell->error)
	{
		g_main.g_return = 1;
		return (1);
	}
	return (0);
}

static int	open_error(void)
{
	g_main.g_return = 1;
	return (-1);
}

void	prepare_input(t_main *shell, t_token *token)
{
	t_token	*desire;

	desire = token->prev;
	while (desire && desire->type != REDIR_IN && desire->type != REDIR_HEREDOC)
		desire = desire->prev;
	desire->skip = TRUE;
	ft_close_fd(shell->fd_in);
}

static int	redirect_input(t_main *shell, t_token *token, int *new_input)
{
	if ((*new_input) == 1)
		prepare_input(shell, token);
	if (token->next)
	{
		shell->fd_in = open(token->next->str, O_RDONLY, S_IRWXU);
		if (shell->fd_in == -1)
			return (return_err(shell));
		else if (dup2(shell->fd_in, 0) == -1)
			return (return_err(shell));
	}
	else
		return (return_err(shell));
	return (0);
}

int	set_redirect(t_main *shell)
{
	int		input;
	int		output;
	t_token	*token;

	token = shell->tokens;
	input = 0;
	output = 0;
	while (token)
	{
		if (is_error(shell))
			break ;
		if (token->type == REDIR_OUT || token->type == REDIR_OUT_2)
			if (redirect_output(shell, token, &output))
				return (open_error());
		if (token->type == REDIR_IN)
			if (redirect_input(shell, token, &input))
				return (open_error());
		if (token->type == REDIR_HEREDOC)
			if (redirect_heredoc(shell, token, &input))
				return (open_error());
		if (g_main.g_run == FALSE)
			return (1);
		token = token->next;
	}
	return (0);
}
