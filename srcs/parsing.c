/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:24:07 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/24 12:48:51 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	parse_cmd(char **line, int cmd_len, int args_len)
{
	t_cmd	cmd;
	int		i;
	int		j;

	cmd.args = ft_calloc(args_len, sizeof(char *));
	if (!cmd.args)
		return (1);
	cmd.fd_in = 1;
	cmd.fd_out = 0;
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

static void	find_operator(char **line, int *i, int *cmd_len, int *args_len)
{
	if (ft_strncmp(line[*i], "|", ft_strlen(line[*i])))
		*cmd_len += 1;
	else
		return ;
	if (ft_strncmp(line[*i], "<", ft_strlen(line[*i]))
		&& ft_strncmp(line[*i], ">", ft_strlen(line[*i]))
		&& ft_strncmp(line[*i], "<<", ft_strlen(line[*i]))
		&& ft_strncmp(line[*i], ">>", ft_strlen(line[*i])))
		*args_len += 1;
	else
		i++;
	i++;
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
		find_operator(line, &i, &cmd_len, &args_len);
	i++;
	if (parse_cmd(line, cmd_len, args_len))
	{
		ft_putstr("Error\nFailed to initiate struct\n", 2);
		exit (EXIT_FAILURE);
	}
	if (line[i])
		parse_line(&line[i]);
}
