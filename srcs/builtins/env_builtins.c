/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:12:39 by mmanuell          #+#    #+#             */
/*   Updated: 2025/02/04 15:44:32 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_env_var(t_data *data, char *var_name, char *value)
{
	int	i;

	i = get_env_index(var_name, data);
	if (i == data->envp_len)
		return (1);
	free (data->envp[i]);
	data->envp[i] = ft_strjoin(var_name, value);
	if (!data->envp[i])
		return (-1);
	return (0);
}

char	*get_env_var(t_data *data, char *var_name)
{
	int	i;

	i = get_env_index(var_name, data);
	if (i == data->envp_len)
		return (ft_calloc(1, 1));
	return (ft_substr(data->envp[i],
			ft_strlen(var_name),
			ft_strlen(data->envp[i]) - ft_strlen(var_name)));
}

int	get_env_index(char *env_var, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->envp_len)
	{
		if (!ft_strncmp(env_var, data->envp[i], ft_strlen(env_var)))
			return (i);
		i++;
	}
	return (i);
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
