/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazrael <aazrael@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:31:28 by aazrael           #+#    #+#             */
/*   Updated: 2022/02/15 09:39:24 by aazrael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_array(char *str, char **array, t_parser *vars)
{
	int	i;
	int	j;
	int	last_space;

	i = vars->i;
	j = vars->j;
	last_space = vars->last_space;
	array[j] = ft_substr(str, last_space, i - last_space);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '|' || str[i] == '>' || str[i] == '<')
	{
		if (str[i] != '|' && (str[i + 1] == '>' || str[i + 1] == '<'))
			array[++j] = ft_substr(str, i++, 2);
		else
			array[++j] = ft_substr(str, i, 1);
		while (ft_isspace(str[++i]))
			continue ;
	}
	vars->last_space = i;
	vars->j = j + 1;
	vars->i = i - 1;
}

char	*parser1(char *str, char **array, int token_ct)
{
	t_parser	var;

	var.i = 0;
	var.j = 0;
	while (ft_isspace(str[var.i]))
		(var.i)++;
	var.last_space = var.i;
	while (str[var.i] != '\0')
	{
		if (str[var.i] == '\'')
			str = handle_quotes(str, &var.i);
		else if (str[var.i] == '"')
			str = handle_double_quotes(str, &var.i);
		else if (str[var.i] == '$')
			str = handle_bucks(str, &var.i);
		else if (ft_issep(str[var.i]))
			add_to_array(str, array, &var);
		(var.i)++;
	}
	if (str[var.last_space] != '\0')
		array[var.j] = ft_substr(str, var.last_space, var.i - var.last_space);
	else if (str[var.last_space] == '\0' && var.j < token_ct)
		array[var.j] = ft_substr(str, var.last_space, var.i - var.last_space);
	return (str);
}

char	*parser0(t_token **token, char *str)
{
	char	**arr;
	int		sep_ct;

	sep_ct = 0;
	if (check_leading_pipe(str) == -1 || parser2(str, &sep_ct) == -1)
	{
		free(str);
		g_main.g_return = 2;
		return (NULL);
	}
	arr = (char **)malloc((sep_ct + 1) * sizeof(*arr));
	if (NULL == arr)
		malloc_err();
	str = parser1(str, arr, sep_ct + 1);
	create_tokens(token, arr, sep_ct + 1);
	free(arr);
	return (str);
}
