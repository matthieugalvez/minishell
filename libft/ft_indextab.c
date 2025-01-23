/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_indextab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:38:30 by mgalvez           #+#    #+#             */
/*   Updated: 2024/12/28 12:38:38 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_indextab(int *tab, int depht)
{
	int	i;
	int	j;
	int	*index_tab;

	index_tab = ft_calloc(sizeof(int), depht);
	if (!index_tab)
		return (NULL);
	i = 0;
	while (i < depht)
	{
		j = i + 1;
		while (j < depht)
		{
			if (tab[i] > tab[j])
				index_tab[i]++;
			else
				index_tab[j]++;
			j++;
		}
		i++;
	}
	return (index_tab);
}
