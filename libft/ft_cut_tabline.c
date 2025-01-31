/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_tabline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:07:44 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/31 15:44:42 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_cut_tabline(char **tab, int i)
{
	free(tab[i]);
	tab[i] = tab[i + 1];
	i++;
	while (tab[i])
	{
		tab[i] = tab[i + 1];
		i++;
	}
}
