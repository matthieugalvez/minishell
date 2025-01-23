/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:24:07 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/23 19:13:08 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	parse_operator(t_cmd *cmd, char **line, int i)
{
	if (!ft_strncmp(line[i], "<<", ft_strlen(line[i])))
	{
		cmd->fd_in = ft_heredoc();
		return (2);
	}
	else if (!ft_strncmp(line[i], "<", ft_strlen(line[i])))
	{
		cmd->fd_in = open(line[i + 1], O_RDONLY);
		return (2);
	}
	else if (!ft_strncmp(line[i], ">>", ft_strlen(line[i])))
	{
		cmd->fd_out = open(line[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		return (2);
	}
	else if (!ft_strncmp(line[i], ">", ft_strlen(line[i])))
	{
		cmd->fd_out = open(line[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		return (2);
	}
	return (0);
}

static int	parse_cmd(char **line, int cmd_len, int args_len)
{
	t_cmd	cmd;
	int		i;
	int		j;

	cmd.args = ft_calloc(args_len, sizeof(char *));
	if (!cmd.args)
		return (1);
	i = 0;
	j = 0;
	while (i < cmd_len)
	{
		i += parse_operator(&cmd, line, i);
		cmd.args[j] = ft_strdup(line[i]);
		if (!cmd.args[j])
		{
			ft_freetab(cmd.args);
			return (1);
		}
		j++;
		i++;
	}
	return (0);
}

void	parse_line(char **line)
{
	int	i;
	int	cmd_len;
	int	args_len;

	i = 0;
	cmd_len = 0;
	args_len = 0;
	while (line[i])
	{
		if (ft_strncmp(line[i], "|", ft_strlen(line[i])))
			cmd_len++;
		else
			break ;
		if (ft_strncmp(line[i], "<", ft_strlen(line[i]))
			&& ft_strncmp(line[i], ">", ft_strlen(line[i]))
			&& ft_strncmp(line[i], "<<", ft_strlen(line[i]))
			&& ft_strncmp(line[i], ">>", ft_strlen(line[i])))
			args_len++;
		else
			i++;
		i++;
	}
	if (parse_cmd(line, cmd_len, args_len))
	{
		ft_putstr("Error\nFailed to initiate struct\n", 2);
		exit (EXIT_FAILURE);
	}
}
