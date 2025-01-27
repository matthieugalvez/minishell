/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:54:08 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/27 15:38:45 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*	if (!ft_strncmp(line[i], "<", 1) || !ft_strncmp(line[i], ">", 1))
	{
		ft_putstr("minishell: syntax error near unexpected token `", 2);
		printf("%c", line[i][0]);
		if (line[i][1] == line[i][0])
			printf("%c'\n", line[i][1]);
		else
			printf("'\n");
	}*/

static int	parse_operator(char **line, int i)
{
}

int	syntax_parsing(char **line, t_data *data)
{
	int	i;
	int	parsing_case;

	i = 0;
	while (line[i])
	{
		if (line[i][0] == '<' || line[i][0] == '>' || line[i][0] == '|')
		{
			if (parse_operator(line, i))
				return (-1);
		}
	}
}
