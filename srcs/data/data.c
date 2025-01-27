/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:06:07 by mmanuell          #+#    #+#             */
/*   Updated: 2025/01/27 15:21:43 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_data(t_data *data, char **envp)
{
	int	len;

	len = 0;
	while (envp[len])
		len ++;
	data->envp_len = len;
	data->envp = ft_calloc(data->envp_len + 1, sizeof (char *));
	if (!data->envp)
	{
		ft_putstr("Error\nFailed to init data struct\n", 2);
		exit(EXIT_FAILURE);
	}
	if (ft_tabcpy(data->envp, envp))
	{
		ft_putstr("Error\nFailed to init data struct\n", 2);
		exit(EXIT_FAILURE);
	}
}
