/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:21:50 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/25 09:36:09 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export(void)
{
	char	**arr;
	int		size;
	int		i;

	arr = malloc_env();
	size = env_size(arr);
	sort_env(arr, size);
	i = 0;
	while (arr[i])
	{
		printf("declare -x %s\n", arr[i]);
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	check_var(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static char	*name_var(char *str)
{
	int		i;
	char	*name;

	while (str[i] && str[i] != '=')
		i++;
	name = ft_substr(str, 0, i);
	return (name);
}

static void	create_var(char *name, char *str)
{
	int	i;

	i = is_in_env(name);
	free(name);
	if (i >= 0 && ft_strchr(str, '='))
	{
		free(__environ[i]);
		__environ[i] = ft_strdup(str);
	}
	else if (i >= 0 && !ft_strchr(str, '='))
		return ;
	else
		__environ = realloc_env(1, str);
}

int	ft_export(t_token *token)
{
	int	ret;

	ret = 0;
	if (!token || (token && token->type != ARG))
		print_export();
	else
	{
		while (token && token->type == ARG)
		{
			if (!check_var(token->str))
				ret = export_error(token->str, 1);
			else
				create_var(name_var(token->str), token->str);
			token = token->next;
		}
	}
	return (ret);
}
