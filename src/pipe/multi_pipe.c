/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:28:41 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/24 17:56:37 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_prev_token(t_token *token)
{
	t_token	*res;
	
	if (!token->prev)
		return (0);
	else if (token->prev->type == PIPE)
		return (token->prev);
	else
	{
		res = token->prev;
		while (res && res->type != PIPE)
			res = res->prev;
	}
	if (res->skip)
	{
		res = res->next;
		while (res->type > BUILTIN)
			res = res->next;
		if (res->prev && res->prev->type >= REDIR_OUT)
			res = res->next;
	}
	return (res);
}

static void	execute_child_mid(t_main *shell, t_token *token, int fd)
{
	if (!token_has_redir_in(shell, get_prev_token(token)))
	{
		if (dup2(shell->fds[fd - 1][0], STDIN) == -1)
			return (shell_err(shell));
		ft_close_fd(shell->fds[fd - 1][1]);
	}
	if (shell->error)
		exit_child();
	if (!token_has_redir_out(shell, get_prev_token(token)))
	{
		if (dup2(shell->fds[fd][1], STDOUT) == -1)
			return (shell_err(shell));
		ft_close_fd(shell->fds[fd][0]);
	}
	if (shell->error)
		exit_child();
	if (get_prev_token(token)->type <= ARG)
		execve_cmd(get_prev_token(token));
	else
	{
		g_main.g_return = execute_builtins(shell, get_prev_token(token));
		free_env();
		exit (g_main.g_return);
	}
}

int	first_pipe(t_main *shell, t_token *token, int fd)
{
	pid_t	parent;
	
	if (pipe(shell->fds[fd]) != 0)
		return_err(shell);
	parent = fork();
	if (parent == -1)
		return_err(shell);
	else
		add_pid_struct(&shell->childs, new_pid_struct(parent));
	if (!parent)
		execute_child_first(shell, token, fd);
	return (0);
}

int	mid_pipe(t_main *shell, t_token *token, int fd)
{
	pid_t	parent;
	
	if (pipe(shell->fds[fd]) != 0)
		return_err(shell);
	parent = fork();
	if (parent == -1)
		return_err(shell);
	else
		add_pid_struct(&shell->childs, new_pid_struct(parent));
	if (!parent)
		execute_child_mid(shell, token, fd);
	ft_close_fd(shell->fds[fd - 1][0]);
	ft_close_fd(shell->fds[fd - 1][1]);
	return (0);

}

int	last_pipe(t_main *shell, t_token *token, int fd)
{
	pid_t	parent;
	pid_t	cmd;

	if (pipe(shell->fds[fd]) != 0)
		return_err(shell);
	parent = fork();
	if (parent == -1)
		return_err(shell);
	else
		add_pid_struct(&shell->childs, new_pid_struct(parent));
	if (!parent)
		execute_child_left(shell, token, fd);
	ft_close_fd(shell->fds[fd - 1][0]);
	ft_close_fd(shell->fds[fd - 1][1]);
	cmd = fork();
	if (cmd == -1)
		return_err(shell);
	else
		add_pid_struct(&shell->childs, new_pid_struct(cmd));
	if (cmd == 0)
		execute_child_right(shell, token, fd);
	ft_close_fd(shell->fds[fd][0]);
	ft_close_fd(shell->fds[fd][1]);
	return (0);


}