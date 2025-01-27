/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:54:29 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/27 16:45:38 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	redirect_std(t_cmd *cmd)
{
	if (cmd->fd_in < 0 || cmd->fd_out < 0)
		exit (EXIT_FAILURE);
	if (cmd->fd_in)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out > 1)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
}

static void	ft_parentprocess(t_cmd *cmd, t_data *data)
{
	if (try_exec_builtins(cmd) == 0)
		exec_builtins(cmd, data);
}

static void	ft_childprocess(t_cmd *cmd, t_data *data)
{
	char	*cmd_path;

	if (try_exec_builtins(cmd) == 1)
	{
		redirect_std(cmd);
		cmd_path = init_cmd_path(cmd, data);
		printf("Path = %s\n", cmd_path);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}

void	ft_exec(t_cmd *cmd, t_data *data)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (!cmd->pid)
		ft_childprocess(cmd, data);
	else
		ft_parentprocess(cmd, data);
}
