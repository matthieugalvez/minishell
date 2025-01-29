/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:44:51 by mmanuell          #+#    #+#             */
/*   Updated: 2025/01/29 10:56:00 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isbuiltin(char *arg)
{
	if (!ft_strncmp(arg, "echo", 5))
		return (0);
	if (!ft_strncmp(arg, "cd", 3))
		return (0);
	if (!ft_strncmp(arg, "pwd", 4))
		return (0);
	if (!ft_strncmp(arg, "export", 7))
		return (0);
	if (!ft_strncmp(arg, "unset", 6))
		return (0);
	if (!ft_strncmp(arg, "env", 4))
		return (0);
	if (!ft_strncmp(arg, "exit", 5))
		return (0);
	return (1);
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

int	parse_cmd(t_cmd *cmd, char **line, int cmd_len, int args_len)
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
		i += get_redirect_fd(cmd, line, i);
		if (i > cmd_len)
			break ;
		cmd->args[j] = ft_strdup(line[i]);
		if (!cmd->args[j])
		{
			ft_freetab(cmd->args);
			return (1);
		}
		j++;
		i++;
	}
	cmd->args[j] = 0;
	cmd->argc = j;
	return (0);
}

int	ft_isvalidinput(char *input)
{
	int	result;

	result = 1;
	while (*input)
	{
		if (!ft_isspace(*input))
		{
			if (*input != '!' && *input != ':')
				result = 0;
		}
		input ++;
	}
	return (result);
}
