/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:50:40 by mgalvez           #+#    #+#             */
/*   Updated: 2024/11/27 15:37:34 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_nbrsize(long nb)
{
	int	nbr_size;

	nbr_size = 0;
	if (nb < 0)
	{
		nbr_size++;
		nb *= -1;
	}
	if (nb == 0)
		nbr_size++;
	while (nb > 0)
	{
		nbr_size++;
		nb /= 10;
	}
	return (nbr_size + 1);
}

char	*ft_itoa(int n)
{
	int		i;
	long	nb;
	char	*nbr;

	nb = (long)n;
	i = ft_nbrsize(nb);
	nbr = malloc(sizeof(char) * i);
	if (!nbr)
		return (NULL);
	if (nb < 0)
	{
		nbr[0] = '-';
		nb *= -1;
	}
	i--;
	nbr[i] = '\0';
	i--;
	while (nb >= 10)
	{
		nbr[i] = (nb % 10) + 48;
		i--;
		nb /= 10;
	}
	nbr[i] = nb + 48;
	return (nbr);
}
