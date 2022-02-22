/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:59:37 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/18 15:34:50 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int ft_pwd(void)
{
    char    *str;

    str = getcwd(NULL, 0);
    if (str)
    {
        ft_putendl_fd(str, 1);
        free(str);
    }
    else
        return (1);
    return (0);
}