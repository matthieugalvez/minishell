/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:15:54 by mmanuell          #+#    #+#             */
/*   Updated: 2025/02/05 15:07:17 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	set_pwd(t_data *data, char *path)
{
	char	*oldpwd;
	char	buf[PATH_MAX + 1];

	ft_bzero(buf, sizeof(buf));
	if (chdir(path) < 0 || !getcwd(buf, sizeof(buf)))
	{
		ft_putstr("minishell: cd: ", 2);
		perror(path);
		free(path);
		return (1);
	}
	free(path);
	oldpwd = get_env_var(data, "PWD=");
	if (!oldpwd)
		return (-1);
	if (set_env_var(data, "OLDPWD=", oldpwd) == -1)
	{
		free(oldpwd);
		return (1);
	}
	free(oldpwd);
	if (set_env_var(data, "PWD=", buf) == -1)
		return (1);
	return (0);
}

int	ft_cd(t_cmd *cmd, t_data *data)
{
	int		i;
	char	*path;

	if (cmd->argc > 2)
	{
		ft_putstr("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (cmd->argc == 1)
	{
		path = get_env_var(data, "HOME=");
		if (!path[0])
		{
			ft_putstr("minishell: cd: HOME not set\n", 2);
			free(path);
			return (1);
		}
	}
	if (cmd->argc == 2)
		path = ft_strdup(cmd->args[1]);
	i = set_pwd(data, path);
	if (i < 0)
		ft_kill(cmd, data);
	return (i);
}
