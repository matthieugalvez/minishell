/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_other.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:24:07 by mgalvez           #+#    #+#             */
/*   Updated: 2025/02/03 16:13:09 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_pipe(t_cmd *cmd, char *arg, int *i)
{
	static int	pipe_fd[2] = {0};

	if (cmd->fd_in)
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

void	tokenize_other(char **line, t_data *data, int cmd_index, int i)
{
	t_cmd		cmd;
	int			cmd_len;
	int			args_len;

	cmd_len = 0;
	args_len = 0;
	ft_bzero(&cmd, sizeof(cmd));
	while (line[i] && ft_strncmp(line[i], "|", 1))
		find_lens(line, &i, &cmd_len, &args_len);
	init_pipe(&cmd, line[i], &i);
	if (parse_cmd(&cmd, line, cmd_len, args_len))
	{
		ft_putstr("Error\nFailed to initiate struct\n", 2);
		data->exit_code = 1;
		ft_exit(NULL, data);
	}
	unquote_args(&cmd, data);
	ft_exec(&cmd, data, line);
	data->pid_tab[cmd_index] = cmd.pid;
	if (line[i])
		tokenize_other(line, data, cmd_index + 1, i);
	else if (cmd.fd_in)
		close (cmd.fd_in);
}
