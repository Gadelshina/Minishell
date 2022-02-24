/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:35:13 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/24 13:26:03 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int    are_there_pipes(t_main *shell)
{
	t_token *token;

	token = shell->tokens;
	while (token)
	{
		if (token->type == PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}

t_token	*search_next_token(t_token *token)
{
	t_token *ret;
	int		n_type;

	ret = token->next;
	if (!ret)
		return (NULL);
	n_type = ret->type;
	if (n_type == PIPE || n_type == REDIR_OUT || n_type == REDIR_OUT_2 \
		|| token->type == PIPE)	
		return (ret);
	// if (token->type == REDIR_OUT || token->type == REDIR_OUT_2)
	// 	ret = token->next;
	if (token->type == REDIR_IN)
		ret = ret->next;
	else if (n_type == CMD || n_type == ARG)
		while (ret && (ret->type == CMD || ret->type == ARG))
			ret = ret->next;
	return (ret);
}

static void loop(t_main *shell, int *pipe)
{
	t_token *token;

	token = shell->tokens;
	if (!count_pipes(shell))
		set_redirect(shell);
 	if (fatal_err(shell))
		return ;
	while (token)
	{
		if (fatal_err(shell))
			break ;
		if (token->skip == TRUE || token->type >= REDIR_OUT)
		{
			if (token->type >= REDIR_OUT)
				token->next->skip = TRUE;
			token = token->next;
			continue ;
		}
		if (token->type == PIPE)
			execute_pipe(shell,token, pipe);
		
		if (token->type <= BUILTIN && !are_there_pipes(shell))
			execute_token(shell, token);
		token = search_next_token(token);
	}       
}

static void wait_child(t_main *shell)
{
	t_pid_t	*tmp;

	if (!are_there_pipes(shell))
		return ;
	tmp = shell->childs;
	while (tmp)
	{
		waitpid(tmp->pid, &g_main.g_return, 0);
		check_status(&g_main.g_return);
		tmp = tmp->next;
	}
	clear_pid_struct(&shell->childs);
}

void	executing(t_main *shell)
{
	int current_pipe;

	g_main.g_run = TRUE;
	current_pipe = 0;
	loop(shell, &current_pipe);
	wait_child(shell);
	g_main.g_run = FALSE;
	unlink("here_doc");
	if (dup2(shell->in, STDIN) == -1)
		return (shell_err(shell));
	if (dup2(shell->out, STDOUT) == -1)
		return (shell_err(shell));
	ft_close_fd(shell->in);
	ft_close_fd(shell->out);
	ft_close_fd(shell->fd_out);
	ft_close_fd(shell->fd_in);
	free(shell->message);
}