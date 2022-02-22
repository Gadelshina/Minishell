/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:57:42 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/22 20:53:00 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_fd(int fd)
{
	if (fd >= 0)
		close (fd);
}

int count_pipes(t_main *shell)
{
	int count;
	t_token *token;

	token = shell->tokens;
	count = 0;
	while (token)
	{
		if (token->type == PIPE)
			count++;
		token = token->next;
	}
	return (count);
}

void    check_status(int *status)
{
	int	ret;

	ret = (*status);
	if (WIFEXITED(ret) != 0)
		ret = WEXITSTATUS(ret);
	else if (WIFSIGNALED(ret) != 0)
	{
		ret = WTERMSIG(*status);
		if (ret == WIFSIGNALED_SIGINT)
			ret = SIGINT_STATUS;
		else if (ret == WIFSIGNALED_SIGQUIT)
			ret = SIGQUIT_STATUS;
	}
	(*status) = ret;
}

void	sort_env(char **arr, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 1;
	while (i < size)
	{
		j = i;
		while (j > 0 && ft_strcmp(arr[j], arr[j - 1]) < 0)
		{
			tmp = arr[j];
			arr[j] = arr[j - 1];
			arr[j - 1] = tmp;
			j--;
		}
		i++;
	}
}