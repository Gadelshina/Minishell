/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:43:31 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/24 19:42:58 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_gline(char *str)
{
	char	*gline;
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	gline = ft_substr(str, 0, i);
	return (gline);
}

static char	*ft_get_remainder(char *str)
{
	char		*rem;
	int			i;
	size_t		b;

	i = 0;
	b = 0;
	if (!str)
		return (0);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (!str[i])
	{
		free(str);
		return (0);
	}
	b = ft_strlen(str) - i - 1;
	i++;
	rem = ft_substr(str, i, b);
	free(str);
	return (rem);
}

static int	ft_check_error(char **buf, int fd, char **line)
{
	if (fd < 0 || !line || 1 <= 0 || (read(fd, 0, 0) == -1))
		return (-1);
	*buf = (char *)malloc(sizeof(char) * (1 + 1));
	if (!*buf)
		return (-1);
	else
		return (1);
}

static int	check_read_bytes(int read_bytes)
{
	if (read_bytes == 0)
		return (0);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	int			read_bytes;
	char		*buf;
	static char	*remainder;
	char		*tmp;

	read_bytes = ft_check_error(&buf, fd, line);
	if (read_bytes < 0)
		return (-1);
	while (!ft_strchr(remainder, '\n') && read_bytes)
	{
		read_bytes = read(fd, buf, 1);
		buf[read_bytes] = '\0';
		if (remainder != NULL)
		{
			tmp = ft_strjoin(remainder, buf);
			free(remainder);
			remainder = tmp;
		}
		else
			remainder = ft_strdup(buf);
	}
	free(buf);
	*line = ft_gline(remainder);
	remainder = ft_get_remainder(remainder);
	return (check_read_bytes(read_bytes));
}
