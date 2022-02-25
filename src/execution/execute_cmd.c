/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:48:55 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/24 19:03:35 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	execute_last_cmd(t_main *shell, t_token *token)
{
	pid_t	parent;
	char	**argv;

	argv = get_argv(token);
	parent = fork();
	if (parent == -1)
		shell_err(shell);
	else if (parent)
	{
		waitpid(parent, &g_main.g_return, 0);
		check_status(&g_main.g_return);
		free_char_list(argv);
	}
	else
		simple_cmd(argv);
}

void	execve_cmd(t_token *token)
{
	char	**argv;

	argv = get_argv(token);
	simple_cmd(argv);
}

void	execute_token(t_main *shell, t_token *token)
{
	if (token->type == BUILTIN)
		execute_builtins(shell, token);
	else if (token->type == ARG || token->type == CMD)
		execute_last_cmd(shell, token);
}
