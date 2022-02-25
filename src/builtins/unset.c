/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazrael <aazrael@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:22:14 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/25 10:15:18 by aazrael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_error(char *str, int export)
{
	if (export)
		ft_putstr_fd("minishell: export: «", 2);
	else
		ft_putstr_fd("minishell: unset: «", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("»: not a valid identifier\n", 2);
	return (1);
}

int	is_in_env(char *name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (__environ[i])
	{
		if (ft_strncmp(name, __environ[i], len) == 0 && \
			(__environ[i][len] == '=' || __environ[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

int	ft_unset(t_token *token)
{
	int	ret;

	ret = 0;
	while (token && token->type == ARG)
	{
		if (check_var(token->str) && is_in_env(token->str) != -1)
			__environ = realloc_env(-1, token->str);
		else if (!check_var(token->str))
			ret = export_error(token->str, 0);
		token = token->next;
	}
	return (ret);
}
