/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getmult.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:55:48 by mgalvez           #+#    #+#             */
/*   Updated: 2024/12/17 18:48:34 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_getmult(int nb)
{
	long	nbr;
	int		radix;

	if (nb == 0)
		return (0);
	nbr = nb;
	if (nbr < 0)
		nbr *= -1;
	radix = 10;
	nbr /= 10;
	while (nbr)
	{
		nbr /= 10;
		radix *= 10;
	}
	return (radix);
}
