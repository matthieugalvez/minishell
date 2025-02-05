/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:21:10 by mmanuell          #+#    #+#             */
/*   Updated: 2025/02/05 14:55:17 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_env_var(char *arg, char *mode)
{
	int	i;

	i = 1;
	if (*arg && (!ft_isalpha(*arg) && *arg != '_'))
	{
		ft_printf_fd(2,
			"minishell: %s: `%s': not a valid identifier\n", mode, arg);
		return (1);
	}
	while (arg[i])
	{
		if ((!ft_isalnum(arg[i]) && arg[i] != '_')
			|| (!ft_strncmp(mode, "unset", 5) && arg[i] == '='))
		{
			if (!ft_strncmp(mode, "export", 6) && arg[i] == '=')
				break ;
			ft_printf_fd(2,
				"minishell: %s: `%s': not a valid identifier\n", mode, arg);
			return (1);
		}
		i ++;
	}
	return (0);
}

static int	is_valid_env_arg(char *arg, char *mode)
{
	if (!*arg)
	{
		ft_printf_fd(2,
			"minishell: %s: `': not a valid identifier\n", mode);
		return (1);
	}
	if (*arg == '-')
	{
		ft_printf_fd(2, "minishell: %s: %c", mode, *arg);
		if (*(arg + 1))
			ft_printf_fd(2, "%c", *(arg + 1));
		ft_printf_fd(2, ": invalid option\n");
		return (1);
	}
	return (is_valid_env_var(arg, mode));
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
					free (var_name);
					ft_kill(cmd, data);
				}
				free (var_name);
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
