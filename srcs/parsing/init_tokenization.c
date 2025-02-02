/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokenization.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:28:38 by mgalvez           #+#    #+#             */
/*   Updated: 2025/02/02 17:52:32 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	waitchildren(t_data *data)
{
	int		i;
	int		status;

	i = 0;
	while (i < data->pid_tab_len)
	{
		waitpid(data->pid_tab[i], &status, 0);
		i++;
	}
	data->exit_code = WEXITSTATUS(status);
	free(data->pid_tab);
	data->pid_tab_len = 0;
}

void	init_tokenization(char **input, t_data *data)
{
	int		parsing_case;

	parsing_case = syntax_parsing(input);
	if (parsing_case > 0)
	{
		data->pid_tab_len = parsing_case + 1;
		data->pid_tab = ft_calloc(sizeof(int), data->pid_tab_len);
		if (!data->pid_tab)
		{
			ft_putstr("Error\nFailed to init pid_tab\n", 2);
			ft_kill(NULL, data);
		}
		parsing_case = 1;
	}
	if (parsing_case == 0)
		tokenize_builtin(input, data);
	else if (parsing_case == 1)
	{
		tokenize_other(input, data, 0);
		waitchildren(data);
	}
	ft_freetab(input);
}
