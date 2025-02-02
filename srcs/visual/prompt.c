/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:39:01 by mmanuell          #+#    #+#             */
/*   Updated: 2025/02/02 15:51:22 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*static int	get_userlen(char *cwd)
{
	int	len;

	len = 0;
	while (*(cwd + len) && *(cwd + len) != '/')
		len++;
	return (len);
}*/

void	get_title(void)
{
	int		fd;
	char	*line;

	fd = open("./srcs/visual/title", O_RDONLY);
	if (fd)
	{
		line = ft_getnextline(fd);
		printf("\033[0;35m");
		while (line)
		{
			printf("%s", line);
			free(line);
			line = ft_getnextline(fd);
		}
		printf("\033[0m\n");
	}
}

char	*get_prompt(void)
{
	char	*fullpath;
	char	*reducepath;
	char	*active_dir;
	char	*prompt;
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	fullpath = ft_calloc(sizeof(char), ft_strlen(cwd) + 1);
	if (!fullpath)
		return (NULL);
	ft_strlcpy(fullpath, cwd, ft_strlen(cwd) + 1);
//	fullpath = ft_strdup(cwd + 6 + get_userlen(cwd + 6) + 1);
	if (ft_strrchr(fullpath, '/'))
		active_dir = ft_strdup(ft_strrchr(fullpath, '/') + 1);
	else
		active_dir = ft_strdup(fullpath);
	if (!active_dir)
	{
		free(fullpath);
		return (NULL);
	}
	reducepath = ft_substr(fullpath, 0,
			ft_strlen(fullpath) - ft_strlen(active_dir));
	if (!reducepath)
	{
		free(fullpath);
		free(active_dir);
		return (NULL);
	}
//	reducepath = ft_strjoin_free2("~/", reducepath);
	free(fullpath);
	active_dir = ft_strjoin_free2("\001\e[36m\002", active_dir);
	if (!active_dir)
	{
		free(fullpath);
		free(reducepath);
		return (NULL);
	}
	active_dir = ft_strjoin_free(active_dir, ": \001\e[0m\002");
	if (!active_dir)
	{
		free(fullpath);
		free(reducepath);
		return (NULL);
	}
	prompt = ft_strjoin(reducepath, active_dir);
	free(reducepath);
	free(active_dir);
	return (prompt);
}
