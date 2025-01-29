/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:36:13 by mmanuell          #+#    #+#             */
/*   Updated: 2025/01/29 13:05:36 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// return (-1)	: malloc error
// return (1)	: arg error
// return (0)	: tout va bien
// return (2)	: pas une builtin
int	exec_builtins(t_cmd *cmd, t_data *data)
{
	if (!ft_strncmp(cmd->args[0], "cd", 3))
		return (ft_cd(cmd));
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
		return (ft_exit(0, cmd, data));
	return (2);
}
