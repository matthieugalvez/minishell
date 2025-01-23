/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:24:07 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/23 18:30:48 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parse_line(char **line)
{
	int	i;
	int	line_len;

	i = 0;
	line_len = 0;
	while (line[i])
	{
		if (ft_strncmp(line[i], "|", ft_strlen(line[i])))
			line_len++;
		else
			break ;
	}
}
