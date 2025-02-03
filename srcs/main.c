/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:07:19 by mmanuell          #+#    #+#             */
/*   Updated: 2025/02/03 13:45:21 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	get_splited_line(char *user_input, t_data *data)
{
	char	**split_user_input;

	add_history(user_input);
	split_user_input = ft_line_spliter(user_input);
	free(user_input);
	if (!split_user_input)
	{
		data->exit_code = 1;
		ft_kill(NULL, data);
	}
	print_linetab("After split", split_user_input);
	if (!split_user_input[0])
		return ;
	ft_expand(split_user_input, data);
	if (!split_user_input)
	{
		data->exit_code = 1;
		ft_kill(NULL, data);
	}
	print_linetab("After expands", split_user_input);
	init_tokenization(split_user_input, data);
}

static int	ft_isvalidinput(char *input)
{
	int	i;

	i = 0;
	if (input[i] == '\n')
	{
		free(input);
		return (1);
	}
	while (input[i])
	{
		if (!ft_isspace(input[i]) && input[i] != '!' && input[i] != ':')
			return (0);
		i++;
	}
	free(input);
	return (1);
}

static void	tty_loop(t_data *data)
{
	char	*user_input;
	char	*prompt;

	signal_handler_init();
	prompt = get_prompt();
	if (!prompt)
	{
		ft_putstr("Error\nFailed to init prompt\n", 2);
		data->exit_code = 1;
		ft_kill(NULL, data);
	}
	user_input = readline(prompt);
	free(prompt);
	if (!user_input)
		ft_exit(NULL, data);
	else
	{
		signal_handler_inchild();
		if (ft_isvalidinput(user_input) == 0)
			get_splited_line(user_input, data);
		tty_loop(data);
	}
}

static void	init_data(t_data *data, char **envp)
{
	int	len;

	data->exit_code = 0;
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
		free(data->envp);
		exit(EXIT_FAILURE);
	}
	data->pid_tab_len = 1;
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
