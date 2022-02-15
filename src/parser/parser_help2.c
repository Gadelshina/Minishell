/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_help2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazrael <aazrael@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:48:57 by aazrael           #+#    #+#             */
/*   Updated: 2022/02/15 09:24:55 by aazrael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser_error(int type, char ch)
{
	if (type == 1)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token «", 2);
		if (ch == '\0')
			ft_putstr_fd("newline", 2);
		else
			ft_putchar_fd(ch, 2);
		ft_putstr_fd("»\n", 2);
	}
	else
		ft_putendl_fd("minishell syn ntax error near unclosed quote", 2);
	return (-1);
}

int	ft_isspace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

int	ft_issep(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13) || c == '|' || c == '>' || c == '<')
		return (1);
	else
		return (0);
}

char	*handle_quotes(char *str, int *start)
{
	int	end;

	end = *start + 1;
	while (str[end] != '\'')
		end++;
	remove_quotes(str, *start, end);
	*start = end - 2;
	return (str);
}

char	*handle_double_quotes(char *str, int *start)
{
	int		end;

	end = *start + 1;
	while (str[end] != '"')
	{
		if (str[end] == '$')
			str = handle_bucks(str, &end);
		end++;
	}
	remove_quotes(str, *start, end);
	*start = end - 2;
	return (str);
}
