/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:54:08 by mgalvez           #+#    #+#             */
/*   Updated: 2025/02/03 18:19:02 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	non_operator_case(char **line, int *parsing_case,
		int *cmd_parsed, int *i)
{
	if (*parsing_case == -1 && *cmd_parsed == 0)
	{
		*cmd_parsed = 1;
		*parsing_case = ft_isbuiltin(line[*i]);
	}
	while (line[*i] && !ft_isoperator(line[*i][0]))
		*i += 1;
}

static int	check_multiple_operator(char *line)
{
	int		i;
	char	operator;
	char	token[2];

	i = 0;
	operator = line[i];
	while (line[i])
	{
		if (line[i] != operator)
		{
			token[0] = line[i];
			if (line[i + 1] == line[i])
				token[1] = line[i + 1];
			else
				token[1] = 0;
			ft_printf_fd(2,
				"minishell: syntax error near unexpected token `%s'\n", token);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	parse_operator(char **line, int i)
{
	char	operator[2];

	if (check_multiple_operator(line[i]))
		return (1);
	operator[0] = line[i][0];
	if (ft_strlen(line[i]) > 2
		|| (ft_strlen(line[i]) > 1 && line[i][1] != operator[0])
		|| ((operator[0] == '|' || operator[0] == '&')
			&& (i == 0 || !line[i + 1]))
		|| (line[i + 1] && ft_isoperator(line[i + 1][0])))
	{
		operator[1] = line[i][1];
		ft_printf_fd(2,
			"minishell: syntax error near unexpected token `%s'\n", operator);
		return (1);
	}
	else if (!line[i + 1] || ft_isoperator(line[i + 1][0]))
	{
		ft_printf_fd(2,
			"minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

int	syntax_parsing(char **line, t_data *data)
{
	int	i;
	int	parsing_case;
	int	cmd_parsed;

	i = 0;
	parsing_case = -1;
	cmd_parsed = 0;
	while (line[i])
	{
		if (line[i][0] == '|')
		{
			data->pid_tab_len++;
			parsing_case = 1;
		}
		if (ft_isoperator(line[i][0]))
		{
			if (parse_operator(line, i))
				return (-1);
			i ++;
		}
		else
			non_operator_case(line, &parsing_case, &cmd_parsed, &i);
	}
	return (parsing_case);
}
