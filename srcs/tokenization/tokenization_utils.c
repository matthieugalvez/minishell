/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:44:51 by mmanuell          #+#    #+#             */
/*   Updated: 2025/02/03 14:42:18 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unquote_args(t_cmd *cmd, t_data *data)
{
	int	i;

	ft_unquote(cmd->args);
	if (!cmd->args)
	{
		data->exit_code = 1;
		ft_exit(cmd, data);
	}
	i = 0;
	while (cmd->args[i])
	{
		if (!cmd->args[i][0])
		{
			free(cmd->args[i]);
			cmd->args[i] = ft_calloc(sizeof(char), 2);
			if (!cmd->args[i])
			{
				data->exit_code = 1;
				ft_kill(cmd, data);
			}
			cmd->args[i][0] = ' ';
		}
		i++;
	}
	print_linetab("After unquote", cmd->args);
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
		{
			ft_freetab(cmd->args);
			return (-1);
		}
		if (i > cmd_len)
			break ;
		cmd->args[j] = ft_strdup(line[i]);
		if (!cmd->args[j])
		{
			ft_freetab(cmd->args);
			return (-1);
		}
		j++;
		i++;
	}
	return (j);
}

int	parse_cmd(t_cmd *cmd, char **line, int cmd_len, int args_len)
{
	int	i;

	cmd->args = ft_calloc(sizeof(char *), args_len + 1);
	if (!cmd->args)
		return (1);
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
	if (ft_strncmp(line[*i], "<", 1) && ft_strncmp(line[*i], ">", 1))
		*args_len += 1;
	else
		*i += 1;
	*i += 1;
	return (0);
}
