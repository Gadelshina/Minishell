/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 19:51:10 by zarachne          #+#    #+#             */
/*   Updated: 2021/11/27 19:51:11 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*lstlst;

	lstlst = lst;
	if (lstlst)
	{
		while (lstlst->next != NULL)
			lstlst = lstlst->next;
		return (lstlst);
	}
	return (NULL);
}
