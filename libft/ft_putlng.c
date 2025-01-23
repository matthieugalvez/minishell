/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlng.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:25:06 by mgalvez           #+#    #+#             */
/*   Updated: 2024/11/29 10:28:20 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	ft_putlng(unsigned long nbr, char *base, int fd)
{
	unsigned long	base_len;
	int				siz;

	base_len = ft_strlen(base);
	siz = 0;
	if (nbr / base_len)
		siz += ft_putlng(nbr / base_len, base, fd);
	ft_putchar(base[nbr % base_len], fd);
	return (siz + 1);
}
