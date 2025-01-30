/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:55:46 by mmanuell          #+#    #+#             */
/*   Updated: 2025/01/30 18:04:25 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(char *env_value, t_data *data)
{
	int		i;
	char	*to_find;
	int		len;

	i = 0;
	to_find = ft_strjoin_free(env_value, "=");
	len = ft_strlen(to_find + 1);
	while (data->envp[i])
	{
		if (!ft_strncmp(to_find + 1, data->envp[i], ft_strlen(to_find + 1)))
		{
			free(to_find);
			return (ft_substr(data->envp[i],
					len,
					ft_strlen(data->envp[i])
					- ft_strlen(to_find + 1)));
		}
		i++;
	}
	free(to_find);
	return (NULL);
}
