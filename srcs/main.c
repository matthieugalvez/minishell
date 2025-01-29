/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:07:19 by mmanuell          #+#    #+#             */
/*   Updated: 2025/01/29 16:23:51 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	parse_input(char **input, t_data *data)
{
	int		parsing_case;

	parsing_case = syntax_parsing(input);
	ft_expand(input, data); //fonction qui gere les expand
	if (!input)
	{
		clear_history();
		exit (EXIT_FAILURE);
	}
	ft_unquote(input);
	if (!input)
	{
		clear_history();
		exit (EXIT_FAILURE);
	}
	if (parsing_case == -1 || !input[0])
		ft_freetab(input);
	else if (parsing_case == 0)
		parse_builtin(input, data);
	else if (parsing_case == 1)
		parse_line(input, data);
}

static void	tty_loop(t_data *data)
{
	char	*user_input;
	char	**split_user_input;

	user_input = readline(get_prompt());
	if (*user_input && ft_isvalidinput(user_input) == 0)
	{
		add_history(user_input);
		split_user_input = ft_line_spliter(user_input);
		free(user_input);
		if (!split_user_input)
		{
			clear_history();
			exit (EXIT_FAILURE);
		}
		parse_input(split_user_input, data);
	}
	tty_loop(data);
}

static void	init_data(t_data *data, char **envp)
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

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 1)
		return (1);
	(void) argv;
	init_data(&data, envp);
	get_title();
	tty_loop(&data);
	return (0);
}
