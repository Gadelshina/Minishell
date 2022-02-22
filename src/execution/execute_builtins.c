/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:33:42 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/22 20:23:24 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_builtins(t_main *shell, t_token *token)
{
	int exit_status;

	if (!ft_strcmp(token->str, "pwd"))
		exit_status = ft_pwd();
	else if (!ft_strcmp(token->str, "echo"))
		exit_status = ft_echo(token->next);
	else if (!ft_strcmp(token->str, "env"))
		exit_status = ft_env();
	else if (!ft_strcmp(token->str, "cd"))
        exit_status = ft_cd(token->next);
	else if (!ft_strcmp(token->str, "export"))
        exit_status = ft_export(token->next);
	else if (!ft_strcmp(token->str, "unset"))
        exit_status = ft_unset(token->next);
	else if (!ft_strcmp(token->str, "exit"))
        exit_status = ft_exit(token->next, shell);
	else
	{
		exit_status = -2;
		ft_putstr_fd("minishell$: builtin error\n", 2);
	}
	g_main.g_return = exit_status;
	return (exit_status);
}