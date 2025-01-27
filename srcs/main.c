/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:07:19 by mmanuell          #+#    #+#             */
/*   Updated: 2025/01/27 16:46:12 by mmanuell         ###   ########.fr       */
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
		if (*user_input)
		{
			split_user_input = ft_line_spliter(user_input);
			if (!split_user_input)
			{
				clear_history();
				exit (EXIT_FAILURE);
			}
			if (ft_strncmp(user_input, "\n", ft_strlen(user_input)))
				add_history(user_input);
			parsing_case = syntax_parsing(split_user_input); //parse la synthax de la ligne et return -1 en cas d'echec, 0 en cas de builtin et 1 en cas de parsing classique (pas encore codee :()
			if (parsing_case == 0)
				parse_builtin(split_user_input, data); //la fonction que tu dois coder : elle se declanche dans le cas ou une seule fonction builtin est appellee
			else if (parsing_case == 1)
				parse_line(split_user_input, data); //ma fonction
			free(user_input);
		}
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
