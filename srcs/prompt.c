/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:39:01 by mmanuell          #+#    #+#             */
/*   Updated: 2025/01/23 16:19:18 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int get_userlen(char *cwd)
{
	int	len;

	len = 0;
	while (*(cwd + len) && *(cwd + len) != '/')
		len++;
	return (len);
}

char	*get_prompt()
{
	char	*path;
	char	*right;
	char	*prompt;
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	path = cwd + 6 + get_userlen(cwd + 6) + 1;
	right = ft_strjoin(path, ": ");
	prompt = ft_strjoin("~/", right);
	return (prompt);
}