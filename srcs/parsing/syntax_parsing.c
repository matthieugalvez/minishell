/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:54:08 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/29 11:00:21 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_dir(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '/' && str[i] != '.')
			return (0);
		i++;
	}
	return (1);
}

static int	non_operator_case(char **line, int *parsing_case,
		int *cmd_parsed, int *i)
{
	if (*parsing_case == 0 && *cmd_parsed == 0)
	{
		*cmd_parsed = 1;
		*parsing_case = ft_isbuiltin(line[*i]);
	}
	while (line[*i] && !ft_isoperator(line[*i][0]))
	{
		if (check_dir(line[*i]))
		{
			ft_putstr("minishell: ", 2);
			ft_putstr(line[*i], 2);
			ft_putstr(": Is a directory\n", 2);
			return (1);
		}
		*i += 1;
	}
	return (0);
}

static int	write_errstr(char *token)
{
	ft_putstr("minishell: syntax error near unexpected token `", 2);
	ft_putstr(token, 2);
	ft_putstr("'\n", 2);
	return (1);
}

static int	parse_operator(char **line, int i)
{
	char	operator[2];

	operator[0] = line[i][0];
	if (ft_strlen(line[i]) > 2
		|| (ft_strlen(line[i]) > 1 && line[i][1] != operator[0])
		|| ((operator[0] == '|' || operator[0] == '&')
			&& (i == 0 || !line[i + 1]))
		|| (line[i + 1] && ft_isoperator(line[i + 1][0])))
	{
		operator[1] = line[i][1];
		return (write_errstr(&operator[0]));
	}
	else if (!line[i + 1] || ft_isoperator(line[i + 1][0]))
		return (write_errstr("newline"));
	return (0);
}

int	syntax_parsing(char **line)
{
	int	i;
	int	parsing_case;
	int	cmd_parsed;

	i = 0;
	parsing_case = 0;
	cmd_parsed = 0;
	while (line[i])
	{
		if (line[i][0] == '|')
			parsing_case = 1;
		if (ft_isoperator(line[i][0]))
		{
			if (parse_operator(line, i))
				return (-1);
			i ++;
		}
		else
		{
			if (non_operator_case(line, &parsing_case, &cmd_parsed, &i))
				return (-1);
		}
	}
	return (parsing_case);
}
