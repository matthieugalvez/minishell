/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:48:22 by mgalvez           #+#    #+#             */
/*   Updated: 2024/11/27 16:07:45 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	ft_putnbr(int n, char *base, int fd)
{
	long	nb;
	int		siz;

	nb = (long)n;
	siz = 0;
	if (nb < 0)
	{
		nb *= -1;
		ft_putchar('-', fd);
		siz++;
	}
	if (nb / ft_strlen(base))
		siz += ft_putnbr(nb / ft_strlen(base), base, fd);
	ft_putchar((base[nb % ft_strlen(base)]), fd);
	return (siz + 1);
}
