/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:17:04 by mmanuell          #+#    #+#             */
/*   Updated: 2025/01/29 16:30:51 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_str_tab(char **tab, int fd)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf_fd(fd, "%d : %s\n", i, tab[i]);
		i ++;
	}
	ft_printf_fd(fd, "\n");
}
