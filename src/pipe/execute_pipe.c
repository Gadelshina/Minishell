/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:53:11 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/23 20:22:58 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	execute_pipe(t_main *shell, t_token *token, int *pipe)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = shell->tokens;
	while (tmp)
	{
		if (tmp->type == PIPE)
			count++;
		tmp = tmp->next;
	}
	if (count == 1)
		lonely_pipe(shell, token, pipe);

}