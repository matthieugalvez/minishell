/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:06:51 by mmanuell          #+#    #+#             */
/*   Updated: 2025/02/04 11:12:39 by mmanuell         ###   ########.fr       */
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

static void	try_print_arg(t_cmd *cmd, int i, int print_flag)
{
	if (!is_flag(cmd->args[i]) || print_flag)
	{
		ft_putstr(cmd->args[i], cmd->fd_out);
		if (i < cmd->argc - 1)
			ft_putstr(" ", cmd->fd_out);
		print_flag = 1;
	}
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
			try_print_arg(cmd, i, print_flag);
	}
	if (!n_option)
		ft_putstr("\n", cmd->fd_out);
	return (0);
}
