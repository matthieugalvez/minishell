/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_linetab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:12:43 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/30 11:49:24 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_linetab(char *str, char **input)
{
	int	i;

	i = 0;
	ft_printf_fd(2, "=========================\n%s : \n", str);
	while (input[i])
	{
		ft_printf_fd(2, "%d : %s\n", i, input[i]);
		i++;
	}
	ft_printf_fd(2, "=========================\n");
}
