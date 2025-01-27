/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:24:07 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/27 12:44:14 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	parse_cmd(t_cmd *cmd, char **line, int cmd_len, int args_len)
{
	int		i;
	int		j;

	cmd->args = ft_calloc(args_len, sizeof(char *) + 1);
	if (!cmd->args)
		return (1);
	i = 0;
	j = 0;
	while (i < cmd_len)
	{
		i += parse_operator(cmd, line, i);
		if (!ft_strncmp(line[i], "<", 1) || !ft_strncmp(line[i], ">", 1))
		{
			ft_putstr("minishell: syntax error near unexpected token `", 2);
			printf("%c", line[i][0]);
			if (line[i][1] == line[i][0])
				printf("%c'\n", line[i][1]);
			else
				printf("'\n");
		}
		cmd->args[j] = ft_strdup(line[i]);
		if (!cmd->args[j])
		{
			ft_freetab(cmd->args);
			return (1);
		}
		j++;
		i++;
	}
	cmd->argc = j;
	return (0);
}

static void	init_pipe(t_cmd *cmd, char *arg, int *i)
{
	static int	pipe_fd[2] = {0};

	cmd->fd_in = pipe_fd[0];
	if (!ft_strncmp(arg, "|", ft_strlen(arg)))
	{
		pipe(&pipe_fd[0]);
		i += 1;
	}
	else
		ft_bzero(&pipe_fd, sizeof(int) * 2);
	if (pipe_fd[1])
		cmd->fd_out = pipe_fd[1];
	else
		cmd->fd_out = 1;
}

static void	find_operator(char **line, int *i, int *cmd_len, int *args_len)
{
	*cmd_len += 1;
	if (ft_strncmp(line[*i], "<", 1) && ft_strncmp(line[*i], ">", 1))
		*args_len += 1;
	else
	{
		if (ft_strlen(line[*i]) < 2 || (ft_strlen(line[*i]) == 2
				&& (line[*i][2] == '<' || line[*i][2] == '>')))
		i += 1;
	}
	i += 1;
}

void	parse_line(char **line, t_data *data)
{
	t_cmd		cmd;
	int			i;
	int			cmd_len;
	int			args_len;

	i = 0;
	cmd_len = 0;
	args_len = 0;
	while (line[i] && ft_strncmp(line[i], "|", ft_strlen(line[i])))
		find_operator(line, &i, &cmd_len, &args_len);
	init_pipe(&cmd, line[i], &i);
	if (parse_cmd(&cmd, line, cmd_len, args_len))
	{
		ft_putstr("Error\nFailed to initiate struct\n", 2);
		exit (EXIT_FAILURE);
	}
	ft_exec(&cmd, data);
	if (line[i])
		parse_line(&line[i], data);
}
