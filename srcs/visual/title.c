/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   title.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:32:02 by mmanuell          #+#    #+#             */
/*   Updated: 2025/02/03 16:32:21 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
