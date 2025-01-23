/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getsmallest.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:59:48 by mgalvez           #+#    #+#             */
/*   Updated: 2024/12/16 11:48:29 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_getsmallest(int *tab, int len)
{
	int	i;
	int	smallest;
	int	smallest_index;

	smallest = tab[0];
	smallest_index = 0;
	i = 1;
	while (i < len)
	{
		if (tab[i] < smallest)
		{
			smallest = tab[i];
			smallest_index = i;
		}
		i++;
	}
	return (smallest_index);
}
