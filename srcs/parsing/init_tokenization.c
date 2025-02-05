/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokenization.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:28:38 by mgalvez           #+#    #+#             */
/*   Updated: 2025/02/05 16:54:08 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_sig_errno = 0;

static void	waitchildren(t_data *data)
{
	int		i;
	int		status;

	status = -1;
	i = 0;
	while (i < data->pid_tab_len)
	{
		waitpid(data->pid_tab[i], &status, 0);
		i++;
	}
	data->exit_code = WEXITSTATUS(status);
	if (status == -1)
		data->exit_code = g_sig_errno;
	free(data->pid_tab);
	data->pid_tab_len = 0;
}

static void	init_tab_len(t_data *data)
{
	data->pid_tab = ft_calloc(sizeof(int), data->pid_tab_len);
	if (!data->pid_tab)
	{
		ft_putstr("Error\nFailed to init pid_tab\n", 2);
		ft_kill(NULL, data);
	}
}

void	init_tokenization(char **input, t_data *data)
{
	int		parsing_case;

	parsing_case = syntax_parsing(input, data);
	if (parsing_case == 0)
		tokenize_builtin(input, data);
	else if (parsing_case == 1)
	{
		init_tab_len(data);
		tokenize_other(input, data, 0, 0);
		waitchildren(data);
	}
	data->pid_tab_len = 1;
	ft_freetab(input);
}
