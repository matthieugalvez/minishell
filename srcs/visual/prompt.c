/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:39:01 by mmanuell          #+#    #+#             */
/*   Updated: 2025/09/10 13:35:03 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_full_path(void)
{
	char	cwd[PATH_MAX];
	char	*fullpath;

	if (!getcwd(cwd, sizeof(cwd)))
	{
		fullpath = ft_calloc(sizeof(char), 2);
		if (!fullpath)
			return (NULL);
		fullpath[0] = '?';
		return (fullpath);
	}
	fullpath = ft_calloc(sizeof(char), ft_strlen(cwd) + 1);
	if (!fullpath)
		return (NULL);
	ft_strlcpy(fullpath, cwd, ft_strlen(cwd) + 1);
	return (fullpath);
}

static char	*get_active_dir(void)
{
	char	*active_dir;
	char	*fullpath;

	fullpath = get_full_path();
	if (!fullpath)
		return (NULL);
	if (ft_strrchr(fullpath, '/'))
		active_dir = ft_strdup(ft_strrchr(fullpath, '/') + 1);
	else
		active_dir = ft_strdup(fullpath);
	free(fullpath);
	if (!active_dir)
	{
		return (NULL);
	}
	return (active_dir);
}

static char	*get_reduce_path(char *active_dir)
{
	char	*reducepath;
	char	*fullpath;

	fullpath = get_full_path();
	if (!fullpath)
		return (NULL);
	reducepath = ft_substr(fullpath, 0,
			ft_strlen(fullpath) - ft_strlen(active_dir));
	if (!reducepath)
	{
		free(fullpath);
		free(active_dir);
		return (NULL);
	}
	free(fullpath);
	return (reducepath);
}

static char	*colorize_dir(char *active_dir, char *reducepath)
{
	active_dir = ft_strjoin_free("\001\e[36m\002", active_dir, 2);
	if (!active_dir)
	{
		free(reducepath);
		return (NULL);
	}
	active_dir = ft_strjoin_free(active_dir, ": \001\e[0m\002", 1);
	if (!active_dir)
	{
		free(reducepath);
		return (NULL);
	}
	return (active_dir);
}

char	*get_prompt(void)
{
	char	*active_dir;
	char	*reducepath;
	char	*prompt;

	active_dir = get_active_dir();
	if (!active_dir)
		return (NULL);
	reducepath = get_reduce_path(active_dir);
	if (!reducepath)
	{
		free(active_dir);
		return (NULL);
	}
	active_dir = colorize_dir(active_dir, reducepath);
	prompt = ft_strjoin(reducepath, active_dir);
	free(reducepath);
	free(active_dir);
	return (prompt);
}
