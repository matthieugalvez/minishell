/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:04:15 by mgalvez           #+#    #+#             */
/*   Updated: 2025/02/03 12:23:17 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*check_pathfound(t_data *data, char *pathfound, char **paths)
{
	ft_freetab(paths);
	if (access(pathfound, X_OK) != 0)
	{
		ft_putstr("minishell: ", 2);
		perror(pathfound);
		data->exit_code = 126;
		free(pathfound);
		return (NULL);
	}
	return (pathfound);
}

static char	*get_pathfound(char *path, char *cmd)
{
	char	*pathfound;

	pathfound = ft_strjoin(path, "/");
	if (!pathfound)
		return (NULL);
	pathfound = ft_strjoin_free(pathfound, cmd);
	if (!pathfound)
		return (NULL);
	return (pathfound);
}

static char	**ft_retrievepath(t_data *data)
{
	int		i;
	char	**env_path;
	char	*paths;

	i = 0;
	while (data->envp[i] && ft_strnstr(data->envp[i], "PATH=", 5) == NULL)
		i++;
	if (!data->envp[i])
	{
		ft_putstr("Error : failed to retrieve path list\n", 2);
		data->exit_code = 1;
		return (NULL);
	}
	paths = ft_strnstr(data->envp[i], "PATH=", 5);
	env_path = ft_split(&paths[5], ':');
	if (!env_path)
	{
		ft_putstr("Error : failed to retrieve path list\n", 2);
		data->exit_code = 1;
		return (NULL);
	}
	return (env_path);
}

char	*ft_findpath(t_data *data, char *cmd)
{
	int		i;
	char	*pathfound;
	char	**paths;

	i = 0;
	paths = ft_retrievepath(data);
	if (!paths)
		return (NULL);
	pathfound = get_pathfound(paths[i], cmd);
	if (!pathfound)
	{
		ft_putstr("Error\nFailed to init pathfound\n", 2);
		data->exit_code = 1;
		return (NULL);
	}
	while (paths[i])
	{
		if (access(pathfound, F_OK) == 0)
			return (check_pathfound(data, pathfound, paths));
		i++;
	}
	ft_freetab(paths);
	ft_printf_fd(2, "minishell: %s: command not found\n", cmd);
	data->exit_code = 127;
	return (NULL);
}

char	*check_path(t_data *data, char *cmd_path)
{
	struct stat	path_stat;

	stat(cmd_path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_printf_fd(2, "minishell: %s: Is a directory\n", cmd_path);
		data->exit_code = 126;
		return (NULL);
	}
	if (access(cmd_path, F_OK) != 0)
	{
		ft_putstr("minishell: ", 2);
		perror(cmd_path);
		data->exit_code = 127;
		return (NULL);
	}
	if (access(cmd_path, X_OK) != 0)
	{
		ft_putstr("minishell: ", 2);
		perror(cmd_path);
		data->exit_code = 126;
		return (NULL);
	}
	return (cmd_path);
}
