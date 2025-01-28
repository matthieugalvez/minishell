/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:20:34 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/28 12:23:07 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_option(char *option)
{
	int	i;

	i = 1;
	while (option[i])
	{
		if (option[i] == 'n')
			i++;
		else
			break ;
	}
	if (!option[i])
	{
		i++;
		return (1);
	}
	return (0);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	n_option;

	i = 1;
	n_option = 0;
	if (!ft_strncmp(cmd->args[i], "-n", 2))
	{
		n_option = check_option(cmd->args[i]);
		i++;
	}
	while (i < cmd->argc - 1)
	{
		ft_putstr(cmd->args[i], cmd->fd_out);
		ft_putstr(" ", cmd->fd_out);
		i++;
	}
	ft_putstr(cmd->args[i], cmd->fd_out);
	if (!n_option)
		ft_putstr("\n", cmd->fd_out);
	return (0);
}

int	ft_cd(char *path)
{
	if (chdir(path))
	{
		printf("cd: ");
		perror(path);
		return (1);
	}
	return (0);
}

int	ft_pwd(t_cmd *cmd)
{
	char	buf[PATH_MAX + 1];

	ft_bzero(buf, sizeof(buf));
	if (!getcwd(buf, sizeof(buf)))
	{
		perror("pwd");
		return (1);
	}
	ft_putstr(buf, cmd->fd_out);
	ft_putstr("\n", cmd->fd_out);
	return (0);
}

void	ft_exit(int exit_code, t_cmd *cmd, t_data *data)
{
	ft_freetab(cmd->args);
	ft_freetab(data->envp);
	exit(exit_code);
}
