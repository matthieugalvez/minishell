/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:54:29 by mgalvez           #+#    #+#             */
/*   Updated: 2025/02/03 14:13:17 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*init_cmd_path(t_cmd *cmd, t_data *data)
{
	char		*cmd_path;

	if (ft_strchr(cmd->args[0], '/'))
	{
		cmd_path = cmd->args[0];
		cmd_path = check_path(data, cmd_path);
	}
	else
		cmd_path = ft_findpath(data, cmd->args[0]);
	return (cmd_path);
}

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

static void	ft_childprocess(t_cmd *cmd, t_data *data, char **line)
{
	char	*cmd_path;

	signal_handler_child();
	ft_freetab(line);
	if (cmd->to_close_fd)
		close(cmd->to_close_fd);
	data->exit_code = exec_builtins(cmd, data);
	if (data->exit_code != 2)
	{
		close(cmd->fd_in);
		close(cmd->fd_out);
		ft_kill(cmd, data);
	}
	else
		data->exit_code = 0;
	redirect_std(cmd);
	cmd_path = init_cmd_path(cmd, data);
	if (!cmd_path)
		ft_kill(cmd, data);
	execve(cmd_path, cmd->args, data->envp);
	perror("minishell: execve");
	data->exit_code = 1;
	ft_kill(cmd, data);
}

void	ft_exec(t_cmd *cmd, t_data *data, char **line)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (!cmd->pid)
		ft_childprocess(cmd, data, line);
	else
	{
		ft_freetab(cmd->args);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
	}
}
