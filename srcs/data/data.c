/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:06:07 by mmanuell          #+#    #+#             */
/*   Updated: 2025/01/24 16:08:07 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	init_envp(t_data *data, char **envp)
{
	int	len;

	len = 0;
	while (envp[len])
		len ++;
	data->envp_len = len;
	data->envp = ft_calloc(data->envp_len + 1, sizeof (char *));
	if (!data->envp)
		return (1);
	if (ft_tabcpy(data->envp, envp))
		return (1);
	return (0);
}

t_data	*init_data(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	if (init_envp(data, envp) == 1)
	{
		free(data);
		return (NULL);
	}
	return (data);
}
