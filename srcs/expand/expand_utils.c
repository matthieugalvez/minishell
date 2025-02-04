/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:55:46 by mmanuell          #+#    #+#             */
/*   Updated: 2025/02/04 13:57:53 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_orphan_dollar(char *env_value)
{
	int	i;

	i = 0;
	while (env_value[i])
	{
		if (env_value[i] != '$')
			return (0);
		i++;
	}
	return (1);
}

static char	*search_env(char *env_value, t_data *data)
{
	int		i;
	int		len;

	i = 0;
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
	return (ft_calloc(sizeof (char), 1));
}

char	*get_env_value(char *env_value, t_data *data)
{
	char	*out;

	if (check_orphan_dollar(env_value))
		out = ft_strdup(env_value);
	else if (env_value[1] == '?')
		out = ft_itoa(data->exit_code);
	else
	{
		out = ft_strjoin(env_value, "=");
		if (!out)
			return (NULL);
		return (search_env(out, data));
	}
	return (out);
}
