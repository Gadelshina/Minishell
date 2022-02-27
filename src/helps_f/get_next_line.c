/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarachne <zarachne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:06:20 by zarachne          #+#    #+#             */
/*   Updated: 2022/02/27 09:14:06 by zarachne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_create_last(char *text, char **line, char *buf)
{
	char	*pos;

	free(buf);
	pos = ft_strchr(text, '\0');
	*line = malloc((pos - text + 1) * sizeof(**line));
	if (*line == NULL)
	{
		free(text);
		return (NULL);
	}
	ft_strlcpy(*line, text, pos - text + 1);
	free(text);
	return (NULL);
}

static int	ft_create_line(char *text, char **line, char *buf)
{
	char	*pos;
	int		i;

	free(buf);
	pos = ft_strchr(text, '\n');
	if (pos != NULL)
	{
		*line = malloc((pos - text + 1) * sizeof(**line));
		if (*line == NULL)
		{
			free(text);
			return (-1);
		}
		ft_strlcpy(*line, text, pos - text + 1);
		i = 0;
		while (pos[i + 1] != '\0')
		{
			text[i] = pos[i + 1];
			i++;
		}
		text[i] = '\0';
	}
	return (1);
}

static int	ft_rd_zero(char **text, char **line, char *buf)
{
	*text = ft_create_last(*text, line, buf);
	return (0);
}

static char	*gnl_strjoin(char *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	i = ft_strlen(s1);
	res = malloc((i + ft_strlen(s2) + 1) * sizeof(*res));
	if (res == NULL)
		return (res);
	if (s1 == NULL)
		ft_strlcpy(res, s2, ft_strlen(s2) + 1);
	else
	{
		ft_strlcpy(res, s1, i + 1);
		j = 0;
		while (s2[j] != '\0')
		{
			res[i] = s2[j];
			i++;
			j++;
		}
		res[i] = '\0';
		free(s1);
	}
	return (res);
}

int	get_next_line(int fd, char **line)
{
	int			rd;
	static char	*text;
	char		*buf;

	if (fd < 0 || line == NULL)
		return (-1);
	buf = malloc(sizeof(*buf) * 2);
	if (buf == NULL)
		return (-1);
	rd = 1;
	while (rd > 0 && ft_strchr(text, '\n') == NULL)
	{
		rd = read(fd, buf, 1);
		if (rd < 0)
		{
			free(buf);
			return (-1);
		}
		buf[rd] = '\0';
		text = gnl_strjoin(text, buf);
	}
	if (rd == 0)
		return (ft_rd_zero(&text, line, buf));
	ft_create_line(text, line, buf);
	return (1);
}
