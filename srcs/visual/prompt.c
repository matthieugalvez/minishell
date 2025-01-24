/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:39:01 by mmanuell          #+#    #+#             */
/*   Updated: 2025/01/24 17:24:38 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_userlen(char *cwd)
{
	int	len;

	len = 0;
	while (*(cwd + len) && *(cwd + len) != '/')
		len++;
	return (len);
}

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
			line = ft_getnextline(fd);
		}
		printf("\033[0m\n");
	}
}

char	*get_prompt(void)
{
	char	*path;
	char	*right;
	char	*prompt;
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	path = cwd + 6 + get_userlen(cwd + 6) + 1;
	right = ft_strjoin(path, ": ");
	prompt = ft_strjoin("~/", right);
	prompt = ft_strjoin("\001\e[0;34m\002", prompt);
	prompt = ft_strjoin(prompt, "\001\e[0m\002");
	return (prompt);
}
