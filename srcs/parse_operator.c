/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:25:51 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/24 15:04:53 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_outfile_append(t_cmd *cmd, char *outfile)
{
	if (cmd->fd_out > 1)
		close(cmd->fd_out);
	cmd->fd_out = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->fd_out < 0)
		perror("outfile");
	return (2);
}

static int	ft_outfile_truncate(t_cmd *cmd, char *outfile)
{
	if (cmd->fd_out > 1)
		close(cmd->fd_out);
	cmd->fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_out < 0)
		perror("outfile");
	return (2);
}

static int	ft_heredoc(t_cmd *cmd, char *limiter)
{
	char	*name;

	if (cmd->fd_in > 0)
		close(cmd->fd_in);
	name = ft_makerngname(12);
	if (!name)
	{
		ft_putstr("Error\nCouldn't generate temp file name\n", 2);
		exit (EXIT_FAILURE);
	}
	cmd->fd_in = get_heredoc_fd(limiter, name);
	free(name);
	return (2);
}

static int	ft_infile(t_cmd *cmd, char *infile)
{
	if (cmd->fd_in > 0)
		close(cmd->fd_in);
	cmd->fd_in = open(infile, O_RDONLY);
	if (cmd->fd_in < 0)
		perror("infile");
	return (2);
}

int	parse_operator(t_cmd *cmd, char **line, int i)
{
	if (!ft_strncmp(line[i], "<", ft_strlen(line[i])))
		return (ft_infile(cmd, line[i + 1]));
	else if (!ft_strncmp(line[i], "<<", ft_strlen(line[i])))
		return (ft_heredoc(cmd, line[i + 1]));
	else if (!ft_strncmp(line[i], ">", ft_strlen(line[i])))
		return (ft_outfile_truncate(cmd, line[i + 1]));
	else if (!ft_strncmp(line[i], ">>", ft_strlen(line[i])))
		return (ft_outfile_append(cmd, line[i + 1]));
	return (0);
}
