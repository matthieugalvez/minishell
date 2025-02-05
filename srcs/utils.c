/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:29:07 by mgalvez           #+#    #+#             */
/*   Updated: 2025/02/05 13:50:49 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_builtins(t_cmd *cmd, t_data *data)
{
	if (!cmd->args[0] || cmd->fd_in < 0 || cmd->fd_out < 0)
		return (1);
	if (!ft_strncmp(cmd->args[0], "cd", 3))
		return (ft_cd(cmd, data));
	if (!ft_strncmp(cmd->args[0], "env", 4))
		return (ft_env(cmd, data, NULL));
	if (!ft_strncmp(cmd->args[0], "export", 7))
		return (ft_export(data, cmd));
	if (!ft_strncmp(cmd->args[0], "unset", 6))
		return (ft_unset(data, cmd));
	if (!ft_strncmp(cmd->args[0], "pwd", 4))
		return (ft_pwd(cmd));
	if (!ft_strncmp(cmd->args[0], "echo", 5))
		return (ft_echo(cmd));
	if (!ft_strncmp(cmd->args[0], "exit", 5))
		return (ft_exit(cmd, data));
	return (2);
}

void	ft_kill(t_cmd *cmd, t_data *data)
{
	if (cmd)
		ft_freetab(cmd->args);
	if (data)
		ft_freetab(data->envp);
	clear_history();
	exit(data->exit_code);
}
