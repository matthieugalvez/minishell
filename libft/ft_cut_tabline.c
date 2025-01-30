/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_tabline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:07:44 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/30 15:03:02 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_cut_tabline(char **tab, int i)
{
	ft_print_str_tab(tab, 2);
	ft_printf_fd(2, "%d\n", i);
	free(tab[i]);
	tab[i] = tab[i + 1];
	i++;
	while (tab[i])
	{
		ft_printf_fd(2, "%d\n", i);
		tab[i] = tab[i + 1];
		i++;
	}
	free(tab[i + 1]);
}
