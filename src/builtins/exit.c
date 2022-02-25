/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:03:22 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/24 19:50:26 by zarachne         ###   ########.fr       */
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
