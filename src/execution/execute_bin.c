/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:44:35 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/24 19:02:19 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**find_paths(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			break ;
		i++;
	}
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	return (paths);
}

static void	print_cmd_err(char **cmd)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(cmd[0], 2);
	free_arr(cmd);
}

static void	exit_err(char **cmd)
{
	print_cmd_err(cmd);
	exit(ERROR_STATUS);
}

static char	*get_path(char **cmd, char **env)
{
	int		i;
	char	*path;
	char	*half_path;
	char	**paths;

	paths = find_paths(env);
	if (!paths)
		exit_err(cmd);
	i = -1;
	while (paths[++i])
	{
		half_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(half_path, cmd[0]);
		free(half_path);
		if (!access(path, 1))
			return (return_path(paths, &path));
		free(path);
	}
	free_arr(paths);
	if (!access(cmd[0], 1))
		return (cmd[0]);
	print_cmd_err(cmd);
	exit (ERROR_STATUS);
}

void	simple_cmd(char **argv)
{
	char	*path;

	path = get_path(argv, __environ);
	g_main.g_return = execve(path, argv, __environ);
	if (g_main.g_return == -1)
	{
		g_main.g_return = ERROR_STATUS;
		perror("minishell");
		exit (ERROR_STATUS);
	}
}
