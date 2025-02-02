/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:08:54 by mmanuell          #+#    #+#             */
/*   Updated: 2025/02/02 13:35:12 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		ft_putstr("Error\nFailed to initiate struct\n", 2);
		exit (EXIT_FAILURE);
	}
	unquote_args(&cmd, data);
	data->exit_code = exec_builtins(&cmd, data);
	if (cmd.fd_in)
		close (cmd.fd_in);
	if (cmd.fd_out > 1)
		close (cmd.fd_out);
}
