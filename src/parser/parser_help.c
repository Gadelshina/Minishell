/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazrael <aazrael@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:51:03 by aazrael           #+#    #+#             */
/*   Updated: 2022/02/10 11:55:26 by aazrael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_leading_pipe(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '|')
		return (parser_error(1, '|'));
	return (i);
}

int	handle_pipe(char *str, int i, int *sep_ct)
{
	i++;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '|' || str[i] == '\0')
		return (parser_error(1, str[i]));
	(*sep_ct) += 2;
	return (i);
}

int	handle_redirection(char *str, int i, int *sep_ct)
{
	i++;
	if (str[i] == str[i - 1])
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (ft_issep(str[i]) || str[i] == '\0')
		return (parser_error(1, str[i]));
	(*sep_ct) += 2;
	return (i);
}

int	handle_sep(char *str, int i, int *sep_ct)
{
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '|')
		i = handle_pipe(str, i, sep_ct);
	else if (str[i] == '>' || str[i] == '<')
		i = handle_redirection(str, i, sep_ct);
	else if (str[i] != '\0')
		(*sep_ct)++;
	return (i - 1);
}

int	parser2(char *str, int *sep_ct)
{
	int	i;
	int	quotes;
	int	duble_quotes;

	quotes = 0;
	duble_quotes = 0;
	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '\'' && !quotes && !duble_quotes)
			quotes = 1;
		else if (str[i] == '"' && !quotes && !duble_quotes)
			duble_quotes = 1;
		else if (str[i] == '\'' && quotes)
			quotes = 0;
		else if (str[i] == '"' && duble_quotes)
			duble_quotes = 0;
		else if (ft_issep(str[i]) && !quotes && !duble_quotes)
			i = handle_sep(str, i, sep_ct);
		if (i == -2)
			return (-1);
	}
	if (quotes || duble_quotes)
		return (parser_error(2, 0));
	return (0);
}
