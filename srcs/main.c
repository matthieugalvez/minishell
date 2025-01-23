/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:07:19 by mmanuell          #+#    #+#             */
/*   Updated: 2025/01/23 16:01:56 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main (int argc, char **argv)
{
	char	*user_input;
	char	**split_user_input;
	
	(void) argv;
	user_input = NULL;
	if (argc != 1)
		return (1);
	
	while (1)
	{
		user_input = readline(get_prompt());
		if (user_input)
		{
			split_user_input = ft_split(user_input, ' ');
			if(!ft_strcmp(user_input,"exit"))
			{
				free(user_input);
				clear_history();
				exit(EXIT_SUCCESS);			
			}
			if(!ft_strcmp(split_user_input[0], "cd"))
				chdir(split_user_input[1]);
			if(ft_strcmp(user_input, "\n"))
				add_history(user_input);
			free(user_input);
		}
	}
}