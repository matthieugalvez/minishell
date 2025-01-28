/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:12:39 by mmanuell          #+#    #+#             */
/*   Updated: 2025/01/28 11:59:19 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_export(t_data *data, char *arg)
{
	int		i;
	char	*var_name;

	var_name = parse_var_name(arg);
	if (!var_name)
		return (1);
	i = get_env_index(var_name, data);
	if (i == data->envp_len)
	{
		data->envp = realloc_envp(data->envp, data->envp_len + 1);
		if (!data->envp)
			return (1);
		data->envp_len += 1;
	}
	data->envp[i] = arg;
	return (0);
}

int	ft_unset(t_data *data, char *arg)
{
	int		i;
	char	*var_name;

	var_name = ft_strjoin(arg, "=");
	if (!var_name)
		return (1);
	i = get_env_index(var_name, data);
	if (i == data->envp_len)
		return (1);
	free(data->envp[i]);
	while (i < data->envp_len)
	{
		data->envp[i] = data->envp[i + 1];
		i++;
	}
	data->envp = realloc_envp(data->envp, data->envp_len);
	if (!data->envp)
		return (1);
	data->envp_len -= 1;
	return (0);
}

int	ft_env(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->envp_len)
	{
		ft_putstr(data->envp[i], cmd->fd_out);
		ft_putstr("\n", cmd->fd_out);
		i++;
	}
	return (0);
}
