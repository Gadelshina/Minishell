/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:48:55 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/22 19:18:09 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_token(t_main *shell, t_token *token)
{
	if (token->type == BUILTIN)
		execute_builtins(shell, token);
}