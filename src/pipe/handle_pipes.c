/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 20:23:23 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/24 13:07:10 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    execute_child_first(t_main *shell, t_token *token, int fd)
{
    t_token *exec_token;

    exec_token = get_prev_token(token);
    set_fd_first(shell, token, fd);
    if (shell->error)
        exit_child();
    if (exec_token->type == ARG || exec_token->type)
        execve_cmd(exec_token);
    else
    {
        g_main.g_return = execute_builtins(shell, exec_token);
        free_env();
        exit (g_main.g_return);
    }
}

void    execute_child_right(t_main *shell, t_token *token, int fd)
{
    t_token *exec_token;

    exec_token = token->next;
    set_fd_last(shell, exec_token, fd);
    if (shell->error)
        exit_child();
    if (exec_token->type == ARG || exec_token->type == CMD)
        execve_cmd(exec_token);
    else
    {
        g_main.g_return = execute_builtins(shell, exec_token);
        free_env();
        exit (g_main.g_return);
    }    
}

int  lonely_pipe(t_main *shell, t_token *token, int fd)
{
	pid_t   parent;
    pid_t   cmd;

    if (pipe(shell->fds[0]) == -1)
        return_err(shell);
    parent = fork();
    if (parent == -1)
        return_err(shell);
    else
        add_pid_struct(&shell->childs, new_pid_struct(parent));
    if (!parent)
        execute_child_first(shell, token, fd);
    cmd = fork();
    if (cmd == -1)
        shell_err(shell);
    else
        add_pid_struct(&shell->childs, new_pid_struct(cmd));
    if (!cmd)
        execute_child_right(shell, token, fd);
    ft_close_fd(shell->fds[0][0]);
    ft_close_fd(shell->fds[0][1]);
    return (0);
}