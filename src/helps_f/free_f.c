/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazrael <aazrael@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 09:15:07 by aazrael           #+#    #+#             */
/*   Updated: 2022/02/25 10:12:18 by aazrael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
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

void	free_on_exit(char **in)
{
	free(*in);
	free_env();
}

void	free_tokens(t_token **token)
{
	while ((*token)->next != NULL)
		(*token) = (*token)->next;
	while ((*token)->prev != NULL)
	{
		(*token) = (*token)->prev;
		free((*token)->next->str);
		(*token)->next->str = NULL;
		free((*token)->next);
		(*token)->next = NULL;
	}
	free((*token)->str);
	(*token)->str = NULL;
	free(*token);
	*token = NULL;
}

char	*return_path(char **paths, char **ret_char)
{
	free_arr(paths);
	return (*ret_char);
}
