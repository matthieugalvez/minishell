/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirect_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:25:51 by mgalvez           #+#    #+#             */
/*   Updated: 2025/02/05 18:14:42 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_outfile_append(t_cmd *cmd, char *outfile)
{
	if (cmd->fd_in < 0 || cmd->fd_out < 0)
		return (2);
	if (cmd->fd_out > 1)
		close(cmd->fd_out);
	outfile = unquote_filename(outfile);
	if (!outfile)
		return (INT_MIN);
	cmd->fd_out = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	free(outfile);
	if (cmd->fd_out < 0)
	{
		ft_putstr("minishell: ", 2);
		perror(outfile);
	}
	return (2);
}

static int	ft_outfile_truncate(t_cmd *cmd, char *outfile)
{
	if (cmd->fd_in < 0 || cmd->fd_out < 0)
		return (2);
	if (cmd->fd_out > 1)
		close(cmd->fd_out);
	outfile = unquote_filename(outfile);
	if (!outfile)
		return (INT_MIN);
	cmd->fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(outfile);
	if (cmd->fd_out < 0)
	{
		ft_putstr("minishell: ", 2);
		perror(outfile);
	}
	return (2);
}

static int	ft_heredoc(t_cmd *cmd, char *limiter)
{
	char	*name;

	if (cmd->fd_in < 0 || cmd->fd_out < 0)
		return (2);
	if (cmd->fd_in > 0)
		close(cmd->fd_in);
	limiter = unquote_filename(limiter);
	if (!limiter)
		return (INT_MIN);
	name = ft_makerngname(12);
	if (!name)
	{
		ft_putstr("Error\nCouldn't generate temp file name\n", 2);
		free(limiter);
		return (INT_MIN);
	}
	cmd->fd_in = get_heredoc_fd(limiter, name);
	free(limiter);
	free(name);
	return (2);
}

static int	ft_infile(t_cmd *cmd, char *infile)
{
	if (cmd->fd_in < 0 || cmd->fd_out < 0)
		return (2);
	if (cmd->fd_in > 0)
		close(cmd->fd_in);
	infile = unquote_filename(infile);
	if (!infile)
		return (INT_MIN);
	cmd->fd_in = open(infile, O_RDONLY);
	free(infile);
	if (cmd->fd_in < 0)
	{
		ft_putstr("minishell: ", 2);
		perror(infile);
	}
	return (2);
}

int	get_redirect_fd(t_cmd *cmd, char **line, int i)
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
