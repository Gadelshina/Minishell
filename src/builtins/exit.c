/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazrael <aazrael@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:03:22 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/25 10:41:56 by aazrael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_arg_num(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == '+' || str[i] == '-') && str[i + 1])
		i++;
	while (str[i])
	{
		if (isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_token *token, t_main *shell)
{
	unsigned int	ret;

	ft_putstr_fd("exit\n", 2);
	shell->exit = TRUE;
	if (token && is_arg_num(token->str) == 0)
	{
		ret = 2;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(token->str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else if (token && token->next)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	else if (token)
		ret = ft_atoi(token->str);
	else
		ret = g_main.g_return;
	return (ret);
}
