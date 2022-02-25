/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazrael <aazrael@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:03:07 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/25 10:33:58 by aazrael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_token *token)
{
	int	flag;

	flag = 0;
	while (token && !ft_strcmp(token->str, "-n"))
	{
		flag = 1;
		token = token->next;
	}
	while (token && token->type == ARG)
	{
		if (token->next && token->next->type == ARG)
			printf("%s ", token->str);
		else
			printf("%s", token->str);
		token = token->next;
	}
	if (!flag)
		printf("\n");
	return (0);
}
