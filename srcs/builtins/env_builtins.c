/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:12:39 by mmanuell          #+#    #+#             */
/*   Updated: 2025/01/31 14:50:46 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_env_var(char *arg)
{
	int	i;

	i = 1;
	if (*arg && (!ft_isalpha(*arg) && *arg != '_'))
	{
		ft_printf_fd(2,
			"minishell: export: '%s': not a valid identifier\n", arg);
		return (1);
	}
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			if (arg[i] == '=')
				break ;
			ft_printf_fd(2,
				"minishell: export: '%s': not a valid identifier\n", arg);
			return (1);
		}
		i ++;
	}
	return (0);
}

static int	is_valid_env_arg(char *arg, char *mode)
{
	if (*arg == '-')
	{
		ft_printf_fd(2, "minishell: %s: %c", mode, *arg);
		if (*(arg + 1))
			ft_printf_fd(2, "%c", *(arg + 1));
		ft_printf_fd(2, ": invalid option\n");
		return (1);
	}
	if (ft_strncmp(mode, "export", 7))
		return (0);
	return (is_valid_env_var(arg));
}

int	ft_export(t_data *data, t_cmd *cmd)
{
	int		cmdi;
	char	*var_name;

	cmdi = 0;
	while (++cmdi < cmd->argc)
	{
		if (!is_valid_env_arg(cmd->args[cmdi], "export"))
		{
			var_name = parse_var_name(cmd->args[cmdi]);
			if (var_name)
			{
				if (add_env_var(data, cmd, var_name, cmdi) == -1)
				{
					data->exit_code = 1;
					ft_kill(cmd, data);
				}
			}
		}
	}
	return (0);
}

int	ft_unset(t_data *data, t_cmd *cmd)
{
	int		cmdi;

	cmdi = 0;
	while (++cmdi < cmd->argc)
	{
		if (!is_valid_env_arg(cmd->args[cmdi], "unset"))
		{
			if (remove_env_var(data, cmd, cmdi) == -1)
			{
				data->exit_code = 1;
				ft_kill(cmd, data);
			}
		}
	}
	return (0);
}

int	ft_env(t_cmd *cmd, t_data *data, char *prefix)
{
	int	i;

	if (cmd->argc > 1)
		return (1);
	i = 0;
	while (i < data->envp_len)
	{
		if (prefix)
			ft_putstr(prefix, cmd->fd_out);
		ft_putstr(data->envp[i], cmd->fd_out);
		ft_putstr("\n", cmd->fd_out);
		i++;
	}
	return (0);
}
