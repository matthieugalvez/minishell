/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:20:34 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/28 17:58:29 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_flag(char *option)
{
	int	i;

	i = 0;
	if (option[i] != '-')
		return (0);
	i = 1;
	while (option[i])
	{
		if (option[i] == 'n')
			i++;
		else
			break ;
	}
	if (!option[i])
		return (1);
	return (0);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	n_option;
	int	print_flag;

	i = 1;
	n_option = 0;
	print_flag = 0;
	if (cmd->argc > 1)
	{
		n_option = is_flag(cmd->args[i]);
		i += is_flag(cmd->args[i]) - 1;
		while (++i < cmd->argc)
		{
			if (!is_flag(cmd->args[i]) || print_flag)
			{
				ft_putstr(cmd->args[i], cmd->fd_out);
				if (i < cmd->argc - 1)
					ft_putstr(" ", cmd->fd_out);
				print_flag = 1;
			}
		}
	}
	if (!n_option)
		ft_putstr("\n", cmd->fd_out);
	return (0);
}

int	ft_cd(t_cmd *cmd)
{
	if (cmd->argc > 2)
	{
		ft_putstr("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (chdir(cmd->args[1]))
	{
		ft_putstr("minishell: cd: ", 2);
		perror(cmd->args[1]);
		return (1);
	}
	return (0);
}

int	ft_pwd(t_cmd *cmd)
{
	char	buf[PATH_MAX + 1];

	ft_bzero(buf, sizeof(buf));
	if (!getcwd(buf, sizeof(buf)))
	{
		perror("pwd");
		return (1);
	}
	ft_putstr(buf, cmd->fd_out);
	ft_putstr("\n", cmd->fd_out);
	return (0);
}

int	ft_exit(int exit_code, t_cmd *cmd, t_data *data)
{
	ft_putstr("exit\n", 2);
	if (cmd->argc > 1)
	{
		if (ft_isint(cmd->args[1]))
		{
			ft_putstr("minishell: exit: ", 2);
			ft_putstr(cmd->args[1], 2);
			ft_putstr(": numeric argument required\n", 2);
		}
		else if (cmd->argc > 2)
		{
			ft_putstr("minishell: exit: too many arguments\n", 2);
			return (1);
		}
	}
	ft_kill(exit_code, cmd, data);
	return (0);
}
