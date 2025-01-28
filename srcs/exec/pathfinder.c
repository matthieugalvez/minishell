/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:04:15 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/28 16:38:13 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**ft_retrievepath(t_data *data)
{
	int		i;
	char	**env_path;
	char	*paths;

	i = 0;
	while (data->envp[i] && ft_strnstr(data->envp[i], "PATH=", 5) == NULL)
		i++;
	if (!data->envp[i])
		return (NULL);
	paths = ft_strnstr(data->envp[i], "PATH=", 5);
	env_path = ft_split(&paths[5], ':');
	if (!env_path)
		return (NULL);
	return (env_path);
}

static char	*ft_findpath(t_data *data, char *cmd)
{
	int		i;
	char	*pathfound;
	char	**paths;

	i = 0;
	paths = ft_retrievepath(data);
	if (!paths)
	{
		ft_putstr("Error : failed to retrieve path list\n", 2);
		return (NULL);
	}
	while (paths[i])
	{
		pathfound = ft_strjoin(paths[i], "/");
		pathfound = ft_strjoin_free(pathfound, cmd);
		if (access(pathfound, X_OK) == 0)
		{
			ft_freetab(paths);
			return (pathfound);
		}
		free(pathfound);
		i++;
	}
	ft_freetab(paths);
	return (NULL);
}

char	*init_cmd_path(t_cmd *cmd, t_data *data)
{
	char	*cmd_path;

	if (ft_strchr(cmd->args[0], '/'))
	{
		cmd_path = cmd->args[0];
		if (access(cmd_path, X_OK) != 0)
		{
			ft_putstr("minishell: ", 2);
			perror(cmd->args[0]);
			return (NULL);
		}
	}
	else
	{
		cmd_path = ft_findpath(data, cmd->args[0]);
		if (!cmd_path)
		{
			ft_putstr("minishell: ", 2);
			ft_putstr(cmd->args[0], 2);
			ft_putstr(": command not found\n", 2);
		}
	}
	return (cmd_path);
}
