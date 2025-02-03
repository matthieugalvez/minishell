/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:08:25 by mmanuell          #+#    #+#             */
/*   Updated: 2025/02/03 17:38:02 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**realloc_envp(char **old_envp, size_t new_size)
{
	char	**new_envp;

	new_envp = ft_calloc((new_size + 1), sizeof (char *));
	if (!new_envp)
		return (NULL);
	if (ft_tabcpy(new_envp, old_envp) == 1)
		return (NULL);
	new_envp[new_size] = NULL;
	ft_freetab(old_envp);
	return (new_envp);
}

char	*parse_var_name(char *arg)
{
	size_t	len;

	len = 0;
	while (*(arg + len) && *(arg + len) != '=')
		len++;
	if (*(arg + len))
		return (ft_substr(arg, 0, len));
	else
		return (NULL);
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

int	add_env_var(t_data *data, t_cmd *cmd, char *var_name, int cmdi)
{
	int	i;

	i = get_env_index(var_name, data);
	if (i == data->envp_len)
	{
		data->envp = realloc_envp(data->envp, data->envp_len + 1);
		if (!data->envp)
			return (-1);
		data->envp_len += 1;
	}
	data->envp[i] = ft_strdup(cmd->args[cmdi]);
	if (!cmd->args[cmdi])
		return (-1);
	return (0);
}

int	remove_env_var(t_data *data, t_cmd *cmd, int cmdi)
{
	char	*var_name;
	int		i;

	var_name = ft_strjoin(cmd->args[cmdi], "=");
	if (!var_name)
		return (-1);
	i = get_env_index(var_name, data) - 1;
	if (i < data->envp_len - 1)
	{
		free(data->envp[i + 1]);
		while (++i < data->envp_len)
			data->envp[i] = data->envp[i + 1];
		data->envp = realloc_envp(data->envp, data->envp_len);
		if (!data->envp)
			return (-1);
		data->envp_len -= 1;
	}
	return (0);
}
