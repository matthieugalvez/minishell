/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:20:34 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/23 18:07:43 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_option(char *option)
{
	int	i;

	i = 0;
	while (option[i])
	{
		if (option[i] == 'n')
			i++;
		else
			break ;
	}
	if (!option[i])
	{
		i++;
		return (1);
	}
	return (0);
}

void	ft_echo(char **args)
{
	int	i;
	int	j;
	int	n_option;

	i = 1;
	if (!ft_strncmp(args[i], "-n", 2))
		n_option = check_option(args[i]);
	else
		n_option = 0;
	while (args[i])
	{
		printf("%s ", args[i]);
		i++;
	}
	if (!n_option)
		printf("\n");
}

void	ft_cd(char *path)
{
	if (chdir(path))
	{
		printf("cd: ");
		perror(path);
	}
}

void	ft_pwd(void)
{
	char	buf[PATH_MAX + 1];

	ft_bzero(buf, sizeof(buf));
	if (!getcwd(buf, sizeof(buf)))
		perror("pwd");
	printf("%s\n", buf);
}
