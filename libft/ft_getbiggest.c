/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getbiggest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:43:42 by mgalvez           #+#    #+#             */
/*   Updated: 2024/12/14 18:57:23 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_getbiggest(int *tab, int len)
{
	int	i;
	int	biggest;
	int	biggest_index;

	biggest = tab[0];
	biggest_index = 0;
	i = 1;
	while (i < len)
	{
		if (tab[i] > biggest)
		{
			biggest = tab[i];
			biggest_index = i;
		}
		i++;
	}
	return (biggest_index);
}
