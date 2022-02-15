/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_help3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazrael <aazrael@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 09:21:59 by aazrael           #+#    #+#             */
/*   Updated: 2022/02/15 09:52:15 by aazrael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(char *str, int start, int end)
{
	int	i;

	i = start;
	while (i < end - 1)
	{
		str[i] = str[i + 1];
		i++;
	}
	while (str[i + 2] != '\0')
	{
		str[i] = str[i + 2];
		i++;
	}
	str[i] = '\0';
}

void	create_tokens(t_token **token, char **array, int token_ct)
{
	int	i;

	i = 0;
	while (i < token_ct)
	{
		ft_add_token(token, ft_new_token());
		if ((*token)->next)
			(*token) = (*token)->next;
		(*token)->str = ft_strdup(array[i]);
		assign_type(*token, array[i]);
		free(array[i]);
		i++;
	}
	while ((*token)->prev != NULL)
		(*token) = (*token)->prev;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
