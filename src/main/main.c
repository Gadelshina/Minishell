/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazrael <aazrael@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:19:00 by aazrael           #+#    #+#             */
/*   Updated: 2022/02/22 15:39:54 by aazrael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_history(char *in)
{
	int	i;

	i = 0;
	while (in[i])
	{
		if (in[i] != ' ')
		{
			add_history(in);
			return ;
		}
		i++;
	}
}

static void	post_init_tokens(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		tmp->skip = FALSE;
		if (tmp->type == CMD && ft_strcmp(tmp->str, "") == 0)
			tmp->skip = TRUE;
		tmp = tmp->next;
	}
}

// void print_tokens(t_token *token)
// {
// 	t_token	*tmp;

// 	tmp = token;
// 	while (tmp)
// 	{
// 		printf("type=	%d str=	%s\n", tmp->type, tmp->str);
// 		tmp = tmp->next;
// 	}
// }

static int	main_cycle(t_main *shell, char **in, t_token **tokens, \
			int first_call)
{
	init1_shell(shell);
	if (shell->error)
		return (2);
	if (*in && !first_call)
		free(*in);
	if (!first_call)
		*in = readline(shell->message);
	if (ctrl_d(shell, *in))
	{
		free(shell->message);
		return (1);
	}
	update_history(*in);
	*in = parser0(tokens, *in);
	if (*in == NULL)
	{
		free(shell->message);
		return (2);
	}
	post_init_tokens(*tokens);
	shell->tokens = *tokens;
	executing(shell);
	free_tokens(tokens);
	return (0);
}

int	main(void)
{
	char	*in;
	char	**array;
	t_main	shell;
	t_token	*tokens;
	int		cycle;

	tokens = NULL;
	in = NULL;
	signal(SIGINT, ft_sig);
	signal(SIGQUIT, ft_sig);
	rl_catch_signals = 0;
	in = readline("$$:");
	init0_shell(&shell, &array);
	cycle = main_cycle(&shell, &in, &tokens, TRUE);
	while (shell.exit == FALSE)
	{
		cycle = main_cycle(&shell, &in, &tokens, FALSE);
		if (cycle == 1)
			break ;
		if (cycle == 2)
			continue ;
	}
	free_on_exit(&in);
	__environ = array;
	return (g_main.g_return);
}
