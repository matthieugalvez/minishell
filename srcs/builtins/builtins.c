/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:20:34 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/27 16:56:44 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	ft_echo(char **args)
{
	int	i;
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
	return (0);
}

int	ft_cd(char *path)
{
	if (chdir(path))
	{
		printf("cd: ");
		perror(path);
		return (1);
	}
	return (0);
}

int	ft_pwd(void)
{
	char	buf[PATH_MAX + 1];

	ft_bzero(buf, sizeof(buf));
	if (!getcwd(buf, sizeof(buf)))
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", buf);
	return (0);
}

void	ft_exit(int exit_code, t_cmd *cmd, t_data *data)
{
	ft_freetab(cmd->args);
	ft_freetab(data->envp);
	exit(exit_code);
}
