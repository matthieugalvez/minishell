/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:54:08 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/28 11:06:12 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_builtin(char *arg)
{
	if (!ft_strncmp(arg, "echo", 5))
		return (0);
	if (!ft_strncmp(arg, "cd", 3))
		return (0);
	if (!ft_strncmp(arg, "pwd", 4))
		return (0);
	if (!ft_strncmp(arg, "export", 7))
		return (0);
	if (!ft_strncmp(arg, "unset", 6))
		return (0);
	if (!ft_strncmp(arg, "env", 4))
		return (0);
	if (!ft_strncmp(arg, "exit", 5))
		return (0);
	return (1);
}

static void	non_operator_case(char **line, int *parsing_case,
		int *cmd_parsed, int *i)
{
	if (*parsing_case == 0 && *cmd_parsed == 0)
	{
		*cmd_parsed = 1;
		*parsing_case = check_builtin(line[*i]);
	}
	while (line[*i]
		&& line[*i][0] != '<' && line[*i][0] != '>' && line[*i][0] != '|')
		*i += 1;
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
	char	operator;

	operator = line[i][0];
	if (ft_strlen(line[i]) > 1 && line[i][1] != operator)
	{
		operator = line[i][1];
		return (write_errstr(&operator));
	}
	else if (ft_strlen(line[i]) > 2)
	{
		operator = line[i][2];
		return (write_errstr(&operator));
	}
	if (operator == '|' && line[i + 1][0] == '|')
		return (write_errstr("|"));
	else if (line[i + 1][0] == '<' || line[i + 1][0] == '>')
	{
		operator = line[i + 1][0];
		return (write_errstr(&operator));
	}
	if (!line[i + 1])
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
		if (line[i][0] == '<' || line[i][0] == '>' || line[i][0] == '|')
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
