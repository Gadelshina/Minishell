/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:53:11 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/25 09:46:09 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_first_pipe(t_token *token)
{
	t_token	*tmp;

	tmp = token->prev;
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (FALSE);
		tmp = tmp->prev;
	}
	return (TRUE);
}

static int	has_next_pipe(t_token *token)
{
	while (token)
	{
		if (token->type == PIPE)
			return (TRUE);
		token = token->next;
	}
	return (FALSE);
}

static int	is_mid_pipe(t_token *token)
{
	t_token	*tmp;
	int		res;

	tmp = token->prev;
	res = has_next_pipe(token->next);
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			res++;
			break ;
		}
		tmp = tmp->prev;
	}
	if (res == 2)
		return (TRUE);
	return (FALSE);
}

static int	is_last_pipe(t_token *token)
{
	t_token	*tmp;

	tmp = token->next;
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (FALSE);
		tmp = tmp->next;
	}
	return (TRUE);
}

void	execute_pipe(t_main *shell, t_token *token, int *pipe)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = shell->tokens;
	while (tmp)
	{
		if (tmp->type == PIPE)
			count++;
		tmp = tmp->next;
	}
	if (count == 1)
		lonely_pipe(shell, token, *pipe);
	else if (is_first_pipe(token))
		first_pipe(shell, token, *pipe);
	else if (is_mid_pipe(token))
		mid_pipe(shell, token, *pipe);
	else if (is_last_pipe(token))
		last_pipe(shell, token, *pipe);
}
