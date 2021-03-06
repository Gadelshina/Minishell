/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:03:07 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/25 11:43:27 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_token *token)
{
	int	flag;

	flag = 0;
	while (token && !ft_strncmp(token->str, "-n", 2))
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
