/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:48:55 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/24 10:43:53 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_token(t_main *shell, t_token *token)
{
	if (token->type == BUILTIN)
		execute_builtins(shell, token);
}

static int	get_size(t_token *token)
{
	int		size;
	t_token	*tmp;

	tmp = token;
	size = 1;
	while (tmp->next && (tmp->next->type == ARG || tmp->next->type == CMD))
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}

static char	**get_argv(t_token *token)
{
	int		i;
	char	**argv;
	int		size;
	t_token	*tmp;

	i = 0;
	tmp = token;
	size = get_size(tmp);
	argv = malloc(sizeof(char *) * (size + 1));
	if (!argv)
		malloc_err();
	while (tmp && (tmp->type == CMD || tmp->type == ARG))
	{
		argv[i] = ft_strdup(tmp->str);
		i++;
		tmp = tmp->next;
	}
	argv[i] = NULL;
	return (argv);
}

void	execve_cmd(t_token *token)
{
	char	**argv;
	
	argv = get_argv(token);
	simple_cmd(argv);
}