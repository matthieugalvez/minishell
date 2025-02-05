/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_other.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:24:07 by mgalvez           #+#    #+#             */
/*   Updated: 2025/02/05 16:27:34 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_pipe(t_cmd *cmd, char *arg, int *i)
{
	static int	pipe_fd[2] = {0};

	if (cmd->fd_in > 0)
		close(cmd->fd_in);
	cmd->fd_in = pipe_fd[0];
	if (arg && !ft_strncmp(arg, "|", 1))
	{
		pipe(&pipe_fd[0]);
		*i += 1;
	}
	else
		ft_bzero(&pipe_fd, sizeof(int) * 2);
	cmd->to_close_fd = pipe_fd[0];
	if (pipe_fd[1])
		cmd->fd_out = pipe_fd[1];
	else
		cmd->fd_out = 1;
}

static void	launch_cmd(t_cmd *cmd, t_data *data, char **line, int cmd_index)
{
	ft_unquote(cmd->args);
	if (!cmd->args)
	{
		data->exit_code = 1;
		ft_exit(cmd, data);
	}
	//print_linetab("After unquote", cmd->args);
	ft_exec(cmd, data, line, cmd_index);
}

void	tokenize_other(char **line, t_data *data, int cmd_index, int i)
{
	t_cmd		cmd;
	int			cmd_len;
	int			args_len;
	int			j;

	cmd_len = 0;
	args_len = 0;
	j = 0;
	ft_bzero(&cmd, sizeof(cmd));
	while (line[i + j] && ft_isoperator(line[i + j][0]) != 2)
		find_lens(&line[i], &j, &cmd_len, &args_len);
	init_pipe(&cmd, line[i + j], &j);
	if (parse_cmd(&cmd, &line[i], cmd_len, args_len))
	{
		data->exit_code = 1;
		ft_kill(&cmd, data);
	}
	//print_linetab("After Tokenisation", cmd.args);
	launch_cmd(&cmd, data, line, cmd_index);
	if (line[i + j])
		tokenize_other(line, data, cmd_index + 1, i + j);
}
