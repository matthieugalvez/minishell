/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:36:13 by mmanuell          #+#    #+#             */
/*   Updated: 2025/01/27 13:13:02 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_builtins(t_data *data, t_cmd *cmd) //return si la builtins a bien fonctionne
{
	if (!ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0]))
		&& cmd->argc == 2)
		return (ft_cd(cmd->args[1]));
	if (!ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0]))
		&& cmd->argc == 1)
		return (ft_env(data));
	if (!ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0]))
		&& cmd->argc == 2)
		return (ft_export(data, cmd->args[1]));
	if (!ft_strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0]))
		&& cmd->argc == 2)
		return (ft_unset(data, cmd->args[1]));
	if (!ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0]))
		&& cmd->argc == 1)
		return (ft_pwd());
	if (!ft_strncmp(cmd->args[0], "echo", ft_strlen(cmd->args[0]))
		&& cmd->argc >= 1)
		return (ft_echo(cmd->args));
	return (1);
}

int	try_exec_builtins(t_cmd *cmd)	//return si la builtins existe
{
	if (!ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0]))
		&& cmd->argc == 2)
		return (0);
	if (!ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0]))
		&& cmd->argc == 1)
		return (0);
	if (!ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0]))
		&& cmd->argc == 2)
		return (0);
	if (!ft_strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0]))
		&& cmd->argc == 2)
		return (0);
	if (!ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0]))
		&& cmd->argc == 1)
		return (0);
	if (!ft_strncmp(cmd->args[0], "echo", ft_strlen(cmd->args[0]))
		&& cmd->argc >= 1)
		return (0);
	return (1);
}