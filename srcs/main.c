/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:07:19 by mmanuell          #+#    #+#             */
/*   Updated: 2025/01/28 16:36:18 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	tty_loop(t_data *data)
{
	int		parsing_case;
	char	*user_input;
	char	**split_user_input;

	while (1)
	{
		user_input = readline(get_prompt());
		if (*user_input && ft_isvalidinput(user_input) == 0)
		{
			split_user_input = ft_line_spliter(user_input);
			if (!split_user_input)
			{
				clear_history();
				exit (EXIT_FAILURE);
			}
			if (ft_strncmp(user_input, "\n", ft_strlen(user_input)))
				add_history(user_input);
			parsing_case = syntax_parsing(split_user_input);
			if (parsing_case == 0)
				parse_builtin(split_user_input, data);
			else if (parsing_case == 1)
				parse_line(split_user_input, data);
		}
		free(user_input);
	}
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
