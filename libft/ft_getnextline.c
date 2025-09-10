/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnextline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:10:50 by mgalvez           #+#    #+#             */
/*   Updated: 2025/02/10 15:37:08 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static char	*ft_store_nextline(char *buf, char *next_line)
{
	int		i;
	int		j;
	char	*next_buf;

	i = 0;
	j = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	next_buf = malloc(sizeof(char) * (ft_strlen(&buf[i]) + 1));
	while (buf[i])
	{
		next_buf[j] = buf[i];
		buf[i] = '\0';
		i++;
		j++;
	}
	next_buf[j] = '\0';
	next_line = ft_strjoin_free(next_line, buf, 1);
	ft_strlcpy(buf, next_buf, BUFFER_SIZE + 1);
	free(next_buf);
	return (next_line);
}

static int	ft_check_nline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_read_nextline_2(char *buf, char *next_line, int fd, int i)
{
	while (buf && ft_check_nline(buf) == 0 && i == BUFFER_SIZE)
	{
		next_line = ft_strjoin_free(next_line, buf, 1);
		if (!next_line)
			return (NULL);
		i = read(fd, buf, BUFFER_SIZE);
		if (i < 0)
		{
			free(next_line);
			return (NULL);
		}
		buf[i] = '\0';
	}
	return (next_line);
}

static char	*ft_read_nextline(char *buf, char *next_line, int fd)
{
	int	i;

	i = read(fd, buf, BUFFER_SIZE);
	if (i < 0)
	{
		free(next_line);
		return (NULL);
	}
	if (i == 0)
	{
		if (next_line[0] == '\0')
		{
			free(next_line);
			return (NULL);
		}
		return (next_line);
	}
	buf[i] = '\0';
	next_line = ft_read_nextline_2(buf, next_line, fd, i);
	return (next_line);
}

char	*ft_getnextline(int fd)
{
	static char	buf[1024][BUFFER_SIZE + 1] = {0};
	char		*next_line;

	if (fd < 0)
		return (NULL);
	next_line = malloc(sizeof(char) * (ft_strlen(buf[fd]) + 1));
	if (!next_line)
		return (NULL);
	if (ft_check_nline(buf[fd]) == 0)
		ft_strlcpy(next_line, buf[fd], BUFFER_SIZE + 1);
	else
	{
		ft_bzero(next_line, ft_strlen(buf[fd]));
		next_line = ft_store_nextline(buf[fd], next_line);
		return (next_line);
	}
	ft_bzero(buf[fd], BUFFER_SIZE + 1);
	next_line = ft_read_nextline(buf[fd], next_line, fd);
	if (!next_line)
		return (NULL);
	next_line = ft_store_nextline(buf[fd], next_line);
	return (next_line);
}
