/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:36:13 by mmanuell          #+#    #+#             */
/*   Updated: 2025/01/27 16:57:53 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_builtins(t_cmd *cmd, t_data *data) //return si la builtins a bien fonctionne
{
	if (!ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0]))
		&& cmd->argc <= 2)
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
	if (!ft_strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0])))
		ft_exit(0, cmd, data);
	return (1);
}

int	try_exec_builtins(t_cmd *cmd)	//return si la builtins existe
{
	int	ret;

	ret = -1;
	if (!ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0])))
		ret = (cmd->argc <= 2);
	if (!ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0])))
		ret = (cmd->argc == 1);
	if (!ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0])))
		ret = (cmd->argc == 2);
	if (!ft_strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0])))
		ret = (cmd->argc == 2);
	if (!ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0])))
		ret = (cmd->argc == 1);
	if (!ft_strncmp(cmd->args[0], "echo", ft_strlen(cmd->args[0])))
		ret = (cmd->argc >= 2);
	if (!ft_strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0])))
		ret = (cmd->argc == 1);
	if (ret == 0)
		printf("%s : Wrong number of arguments\n", cmd->args[0]);
	if (ret == -1)
		printf("Unknown Builtin : %s \n", cmd->args[0]);
	return (ret);
}
