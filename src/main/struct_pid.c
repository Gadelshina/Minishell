/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_pid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazrael <aazrael@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:29:50 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/25 10:07:49 by aazrael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_pid_struct(t_pid_t **first)
{
	t_pid_t	*child;
	t_pid_t	*next_child;

	if (!first)
		return ;
	child = *first;
	while (child)
	{
		next_child = child->next;
		free(child);
		child = next_child;
	}
	*first = NULL;
}

t_pid_t	*new_pid_struct(pid_t pid)
{
	t_pid_t	*new;

	new = malloc(sizeof(t_pid_t));
	if (!new)
		return (NULL);
	new->pid = pid;
	new->next = NULL;
	return (new);
}

static t_pid_t	*search_last(t_pid_t *first)
{
	if (!first)
		return (NULL);
	while (first->next)
		first = first->next;
	return (first);
}

void	add_pid_struct(t_pid_t **first, t_pid_t *new)
{
	t_pid_t	*last;

	if (!first && !new)
		return ;
	if (!*first)
	{
		*first = new;
		return ;
	}
	last = search_last(*first);
	last->next = new;
}
