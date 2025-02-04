/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:15:54 by mmanuell          #+#    #+#             */
/*   Updated: 2025/02/04 18:45:49 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	set_pwd(t_data *data, char *path)
{
	char	*oldpwd;
	char	buf[PATH_MAX + 1];

	ft_bzero(buf, sizeof(buf));
	if (!getcwd(buf, sizeof(buf)))
	{
		ft_putstr("minishell: cd: ", 2);
		perror(path);
		free(path);
		return (1);
	}
	free(path);
	oldpwd = get_env_var(data, "PWD=");
	if (!oldpwd)
		return (1);
	if (set_env_var(data, "OLDPWD=", oldpwd) == -1)
		return (1);
	if (set_env_var(data, "PWD=", buf) == -1)
		return (1);
	return (0);
}

int	ft_cd(t_cmd *cmd, t_data *data)
{
	char	*path;

	if (cmd->argc > 2)
	{
		ft_putstr("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (cmd->argc == 1)
		path = get_env_var(data, "HOME=");
	if (cmd->argc == 2)
		path = ft_strdup(cmd->args[1]);
	if (chdir(path) < 0)
	{
		ft_putstr("minishell: cd: ", 2);
		perror(path);
		free(path);
		return (1);
	}
	return (set_pwd(data, path));
}
