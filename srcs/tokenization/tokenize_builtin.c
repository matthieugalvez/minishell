/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:08:54 by mmanuell          #+#    #+#             */
/*   Updated: 2025/02/05 16:12:41 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	cleanup_builtin(t_cmd *cmd, t_data *data)
{
	data->exit_code = exec_builtins(cmd, data);
	if (cmd->fd_in > 0)
		close (cmd->fd_in);
	if (cmd->fd_out > 1)
		close (cmd->fd_out);
	ft_freetab(cmd->args);
}

void	tokenize_builtin(char **line, t_data *data)
{
	t_cmd		cmd;
	int			i;
	int			cmd_len;
	int			args_len;

	i = 0;
	cmd_len = 0;
	args_len = 0;
	cmd.fd_out = 1;
	cmd.fd_in = 0;
	while (line[i])
		find_lens(line, &i, &cmd_len, &args_len);
	if (parse_cmd(&cmd, line, cmd_len, args_len))
	{
		data->exit_code = 1;
		ft_kill(&cmd, data);
	}
	//print_linetab("After Tokenisation", cmd.args);
	ft_unquote(cmd.args);
	if (!cmd.args)
	{
		data->exit_code = 1;
		ft_exit(&cmd, data);
	}
	//print_linetab("After unquote", cmd.args);
	cleanup_builtin(&cmd, data);
}
