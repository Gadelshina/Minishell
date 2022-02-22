/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:39:17 by svirgil           #+#    #+#             */
/*   Updated: 2022/02/22 14:53:58 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sig(int code)
{
	if (code == SIGINT && !g_main.g_run)
	{
		g_main.g_return = SIGINT_STATUS;
		ft_putstr_fd("^C\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	if (code == SIGQUIT && !g_main.g_run)
		return ;
	if (g_main.g_run)
	{
		if (code == SIGQUIT && g_main.g_here_doc == FALSE)
		{
			ft_putstr_fd("Quit\n", 1);
		}
		else if (code == SIGINT)
		{
			g_main.g_run = FALSE;
			ft_putstr_fd("^C\n", 1);
		}
	}
}

void	on_eof(t_main *shell)
{
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	ft_putstr_fd("exit\n", 1);
	shell->exit = TRUE;
}

int	ctrl_d(t_main *shell, char *in)
{
	if (in == NULL)
	{
		on_eof(shell);
		return (TRUE);
	}
	return (FALSE);
}

void	ft_signal_heredoc(int code)
{
	if (code == SIGINT)
	{
		free_env();
		exit (130);
	}
	if (code == SIGQUIT)
		return ;
}

