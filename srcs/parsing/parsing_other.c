/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_other.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:24:07 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/28 12:16:25 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_pipe(t_cmd *cmd, char *arg, int *i)
{
	static int	pipe_fd[2] = {0};

	cmd->fd_in = pipe_fd[0];
	if (arg && !ft_strncmp(arg, "|", 1))
	{
		pipe(&pipe_fd[0]);
		*i += 1;
	}
	else
		ft_bzero(&pipe_fd, sizeof(int) * 2);
	if (pipe_fd[1])
		cmd->fd_out = pipe_fd[1];
	else
		cmd->fd_out = 1;
}

void	parse_line(char **line, t_data *data)
{
	t_cmd		cmd;
	int			status;
	int			i;
	int			cmd_len;
	int			args_len;

	i = 0;
	cmd_len = 0;
	args_len = 0;
	while (line[i] && ft_strncmp(line[i], "|", 1))
		find_lens(line, &i, &cmd_len, &args_len);
	init_pipe(&cmd, line[i], &i);
	if (parse_cmd(&cmd, line, cmd_len, args_len))
	{
		ft_putstr("Error\nFailed to initiate struct\n", 2);
		exit (EXIT_FAILURE);
	}
	ft_exec(&cmd, data);
	if (line[i])
		parse_line(&line[i], data);
	waitpid(cmd.pid, &status, 0);
}
