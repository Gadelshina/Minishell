/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 08:48:57 by aazrael           #+#    #+#             */
/*   Updated: 2022/02/24 19:42:21 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

char	**malloc_env(void)
{
	int		size;
	int		i;
	char	**arr;

	size = env_size(__environ);
	arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (NULL == arr)
		malloc_err();
	i = -1;
	while (++i < size)
		arr[i] = ft_strdup(__environ[i]);
	arr[i] = NULL;
	return (arr);
}

static void	delete_var(char **arr, char *str, int size)
{
	int	i;
	int	j;
	int	len;

	len = ft_strlen(str);
	i = 0;
	j = 0;
	while (i < size)
	{
		if (!ft_strncmp(str, __environ[i], len) && \
			(__environ[i][len] == '=' || __environ[i][len] == '\0'))
		{
			free(__environ[i]);
			i++;
			continue ;
		}
		arr[j] = ft_strdup(__environ[i]);
		free(__environ[i]);
		j++;
		i++;
	}
}

char	**realloc_env(int add, char *str)
{
	int		i;
	int		size;
	char	**arr;

	size = env_size(__environ);
	arr = malloc(sizeof(char *) * (size + add + 1));
	if (!arr)
		malloc_err();
	if (add > 0)
	{
		i = 0;
		while (i < size)
		{
			arr[i] = ft_strdup(__environ[i]);
			free(__environ[i]);
			i++;
		}
		arr[i] = ft_strdup(str);
	}
	else
		delete_var(arr, str, size);
	arr[size + add] = NULL;
	free(__environ);
	return (arr);
}

void	free_env(void)
{
	int	i;

	i = 0;
	while (__environ[i] != NULL)
	{
		free(__environ[i]);
		i++;
	}
	free(__environ);
}
