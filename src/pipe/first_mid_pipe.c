/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_mid_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:28:41 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/23 21:39:28 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *get_prev_token(t_token *token)
{
    t_token *res;
    
    if (!token->prev)
        return (0);
    else if (token->prev->type == PIPE)
        return (token->prev);
    else
    {
        res = token->prev;
        while (res && res->type != PIPE)
            res = res->prev;
    }
    if (res->skip)
    {
        res = res->next;
        while (res->type > BUILTIN)
            res = res->next;
        if (res->prev && res->prev->type >= REDIR_OUT)
            res = res->next;
    }
    return (res);
}
