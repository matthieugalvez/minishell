/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:07:19 by mmanuell          #+#    #+#             */
/*   Updated: 2025/01/24 12:24:47 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*user_input;
	char	**split_user_input;
	t_data	*data;

	if (argc != 1)
		return (1);
	(void) argv;
	data = malloc(sizeof(t_data));
	if (!data)
	{
		perror("Malloc Error");
		return (EXIT_FAILURE);
	}
	data->envp = envp;
	while (1)
	{
		user_input = readline(get_prompt());
		if (user_input)
		{
			split_user_input = ft_split(user_input, ' ');
			if (!ft_strncmp(user_input, "exit", ft_strlen(user_input)))
			{
				free(user_input);
				clear_history();
				exit(EXIT_SUCCESS);
			}
			if (!ft_strncmp(split_user_input[0], "cd",
					ft_strlen(split_user_input[0])))
				chdir(split_user_input[1]);
			if (ft_strncmp(user_input, "\n", ft_strlen(user_input)))
				add_history(user_input);
			if (!ft_strncmp(user_input, "env", ft_strlen(user_input)))
				ft_env(data);
			free(user_input);
		}
	}
	return (0);
}
