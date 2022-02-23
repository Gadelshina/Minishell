/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:26:46 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/23 16:13:20 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int cd_error(char *str, int mode)
{
	if (mode == 1)
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
	}
	return (1);
}

static void	rewrite_pwd(char *pwd)
{
	int	i;

	i = 0;
	if (getenv("PWD"))
	{
		while(__environ[i])
		{
			if (!ft_strncmp("PWD=", __environ[i], 4))
			{
				free(__environ[i]);
				__environ[i] = ft_strjoin("PWD=", pwd);
				free(pwd);
				return ;
			}
			i++;
		}
	}
	else
		free(pwd);
}

static void	rewrite_oldpwd(char *oldpwd)
{
	int		i;
	char	*tmp;

	i = 0;
	rewrite_pwd(getcwd(NULL, 0));
	if (getenv("OLDPWD"))
	{
		while (__environ[i])
		{
			if (!ft_strncmp("OLDPWD=", __environ[i], 7))
			{
				free(__environ[i]);
				__environ[i] = ft_strjoin("OLDPWD=", oldpwd);
				free(oldpwd);
				return ;
			}
			i++;
		}
	}
	tmp = ft_strjoin("OLDPWD", oldpwd);
	__environ = realloc_env(1, tmp);
	free(oldpwd);
	free(tmp);
}

static int	change_dir(char *str)
{
	int		ret;
	char	*oldpwd;
	char	*direct;

	direct  = getenv(str);
	if (direct)
	{
		oldpwd = getcwd(NULL, 0);
		ret = chdir(direct);
		if (!ret)
			rewrite_oldpwd(oldpwd);
		else
		{
			cd_error(direct, 2);
			free (oldpwd);
		}
		return (ret);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" not set\n", 2);
		return (1);
	}
}

int ft_cd(t_token *token)
{
	int		ret;
	char	*oldpwd;

	if (token && token->next && token->next->type == ARG)
		ret = cd_error(token->str, 1);
	else if (!token || (token && token->type != ARG))
		ret = change_dir("HOME");
	else if (!ft_strcmp(token->str, "-"))
		ret = change_dir("OLDPWD");
	else
	{
		oldpwd = getcwd(NULL, 0);
		ret = chdir(token->str);
		if (ret == 0)
			rewrite_oldpwd(oldpwd);
		else
		{
			ret = cd_error(token->str, 2);
			free(oldpwd);
		}
	}
	return (ret);
}