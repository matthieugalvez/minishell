/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:55:46 by mmanuell          #+#    #+#             */
/*   Updated: 2025/02/05 17:11:21 by mmanuell         ###   ########.fr       */
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

char	*get_expand_value(char *env_value, int double_quote, t_data *data)
{
	char	*out;
	char	*trim;

	if (check_orphan_dollar(env_value))
		out = ft_strdup(env_value);
	else if (env_value[1] == '?')
		out = ft_itoa(data->exit_code);
	else
	{
		out = ft_strjoin(env_value, "=");
		if (!out)
			return (NULL);
		out = search_env(out, data);
		if (double_quote == -1)
		{
			trim = ft_strtrim(out, " ");
			free(out);
			return (trim);
		}
	}
	return (out);
}

char	*expand_passquotes(char *input, int i)
{
	char	*out;

	if (input[i + 1] && input[i] == input[i + 1])
		out = ft_substr(input, i - 1, 3);
	else if (input[i] == '?')
		out = ft_substr(input, i - 1, 2);
	else
	{
		out = ft_calloc(3, sizeof(char));
		if (!out)
			return (NULL);
		out[0] = ' ';
		out[1] = 0;
	}
	return (out);
}
