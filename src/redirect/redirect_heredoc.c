/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:56:27 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/25 13:47:07 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_err(void)
{
	perror("here_doc error");
	exit (EXIT_FAILURE);
}

static void	execute_parent(t_main *shell, pid_t pid)
{
	waitpid(pid, &g_main.g_return, 0);
	check_status(&g_main.g_return);
	if (!g_main.g_return)
	{
		shell->fd_in = open("here_doc", O_RDONLY);
		if (shell->fd_in < 0 || read(shell->fd_in, 0, 0) < 0)
			shell_err(shell);
		else if (dup2(shell->fd_in, 0) == -1)
			shell_err(shell);
		ft_close_fd(shell->fd_in);
	}
}

static int	create_file(t_token *token)
{
	int		fd;
	int		len;
	char	*str;


	fd = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (fd < 0 || read(fd, 0, 0) < 0)
		heredoc_err();
	write(0, "> ", 2);
	while (get_next_line(0, &str) && g_main.g_run)
	{
		len = ft_strlen(token->next->str);
		if (!ft_strncmp((const char *)str, token->next->str, len + 1))
			break ;
		ft_putendl_fd(str, fd);
		free (str);
		write(0, "> ", 2);
	}
	if (!*str)
		ft_putstr_fd("warning: here-document delimited by end-of-file\n", 2);
	if (g_main.g_run)
		free(str);
	ft_close_fd(fd);
	if (g_main.g_run)
		return (0);
	return (1);
}

void	execute_heredoc(t_main *shell, t_token *token)
{
	pid_t	parent;

	parent = fork();
	if (parent == -1)
		return (shell_err(shell));
	if (parent)
		execute_parent(shell, parent);
	else if (!parent)
	{
		signal(SIGINT, ft_signal_heredoc);
		signal(SIGQUIT, ft_signal_heredoc);
		if (dup2(shell->in, STDIN) == -1)
			return (shell_err(shell));
		ft_close_fd(shell->in);
		if (!create_file(token))
		{
			free_env();
			exit (0);
		}

	}
}

int	redirect_heredoc(t_main *shell, t_token *token, int *new_input)
{
	if ((*new_input) == 1)
	{
		prepare_input(token)->skip = TRUE;
		ft_close_fd(shell->fd_in);
	}
	if (token->next)
	{
		g_main.g_here_doc = TRUE;
		execute_heredoc(shell, token);
		g_main.g_here_doc = FALSE;
		(*new_input) = TRUE;
	}
	else
		return_err(shell);
	return (0);
}
