/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:08:54 by mmanuell          #+#    #+#             */
/*   Updated: 2025/01/27 16:38:28 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_builtin(char **line, t_data *data)
{
	t_cmd		cmd;
	int			argc;

	argc = 0;
	while (line[argc])
		argc++;
	cmd.args = line;
	cmd.argc = argc;
	if (try_exec_builtins(&cmd) == 1)
		exec_builtins(&cmd, data);
	else
		printf("Unknown Builtin : %s \n", line[0]);
}