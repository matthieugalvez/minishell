/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:55:46 by mmanuell          #+#    #+#             */
/*   Updated: 2025/01/31 16:04:03 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(char *env_value, t_data *data)
{
	int		i;
	int		len;

	i = 0;
	if (env_value[1] == '?')
	{
		free(env_value);
		return (ft_itoa(data->exit_code));
	}
	env_value = ft_strjoin_free(env_value, "=");
	len = ft_strlen(&env_value[1]);
	while (data->envp[i])
	{
		if (!ft_strncmp(&env_value[1], data->envp[i], ft_strlen(&env_value[1])))
		{
			free(env_value);
			return (ft_substr(data->envp[i], len,
					ft_strlen(data->envp[i]) - len));
		}
		i++;
	}
	free(env_value);
	return (NULL);
}
