/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:55:55 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/24 14:28:28 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_writetemp(int fd, char *name, char *limiter)
{
	char	*buf;

	buf = ft_getnextline(STDIN_FILENO);
	if (!buf)
	{
		free(name);
		ft_putstr("Error\nCouldn't retrieve STDIN line\n", 2);
		return (NULL);
	}
	while (ft_strncmp(limiter, buf, ft_strlen(buf) != 0))
	{
		write(fd, buf, ft_strlen(buf));
		free(buf);
		buf = ft_getnextline(STDIN_FILENO);
		if (!buf)
		{
			free(name);
			ft_putstr("Error\nCouldn't retrieve STDIN line\n", 2);
			return (NULL);
		}
	}
	free(buf);
	return (name);
}

int	get_heredoc_fd(char *limiter, char *name)
{
	int		fd;

	limiter = ft_strjoin(limiter, "\n");
	if (!limiter)
		return (-1);
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("heredoc temp file");
		return (fd);
	}
	name = ft_writetemp(fd, name, limiter);
	free(limiter);
	close(fd);
	if (!name)
		exit (EXIT_FAILURE);
	fd = open(name, O_RDONLY);
	if (fd < 0)
		perror("heredoc");
	return (fd);
}
