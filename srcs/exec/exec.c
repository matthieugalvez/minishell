/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:54:29 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/31 11:35:27 by mgalvez          ###   ########.fr       */
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

static void	ft_childprocess(t_cmd *cmd, t_data *data)
{
	char	*cmd_path;

	if (cmd->to_close_fd)
		close(cmd->to_close_fd);
	if (exec_builtins(cmd, data) == 0)
		ft_kill(EXIT_SUCCESS, cmd, data);
	redirect_std(cmd);
	cmd_path = init_cmd_path(cmd, data);
	if (!cmd_path)
		ft_kill(127, cmd, data);
	execve(cmd_path, cmd->args, data->envp);
	perror("minishell: execve");
	ft_kill(EXIT_FAILURE, cmd, data);
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
	{
		free(cmd->args);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
	}
}
