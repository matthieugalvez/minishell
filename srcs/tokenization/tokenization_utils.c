/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:44:51 by mmanuell          #+#    #+#             */
/*   Updated: 2025/02/05 11:55:55 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	write_args(t_cmd *cmd, char **line, int *i, int *j)
{
	cmd->args[*j] = ft_strdup(line[*i]);
	if (!cmd->args[*j])
	{
		ft_freetab(cmd->args);
		return (1);
	}
	*j += 1;
	*i += 1;
	return (0);
}

static int	check_redirect(t_cmd *cmd, char **line, int cmd_len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cmd_len)
	{
		i += get_redirect_fd(cmd, line, i);
		if (i < 0)
			return (-1);
		if (i >= cmd_len)
			break ;
		if (!ft_isoperator(line[i][0]))
			if (write_args(cmd, line, &i, &j))
				return (-1);
	}
	return (j);
}

int	parse_cmd(t_cmd *cmd, char **line, int cmd_len, int args_len)
{
	int	i;

	cmd->args = ft_calloc(sizeof(char *), args_len + 1);
	if (!cmd->args)
	{
		ft_putstr("Error\nFailed to initiate args tab\n", 2);
		return (1);
	}
	i = check_redirect(cmd, line, cmd_len);
	if (i < 0)
		return (1);
	cmd->args[i] = 0;
	cmd->argc = i;
	return (0);
}

int	find_lens(char **line, int *i, int *cmd_len, int *args_len)
{
	*cmd_len += 1;
	if (!ft_isoperator(line[*i][0]))
		*args_len += 1;
	else
	{
		*cmd_len += 1;
		*i += 1;
	}
	*i += 1;
	return (0);
}
