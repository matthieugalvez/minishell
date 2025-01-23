/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:33:57 by mgalvez           #+#    #+#             */
/*   Updated: 2024/11/29 10:35:02 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	ft_putaddress(void *address)
{
	int	siz;

	if (!address)
	{
		ft_putstr("(nil)", 1);
		return (5);
	}
	siz = ft_putstr("0x", 1);
	siz += ft_putlng((unsigned long)address, "0123456789abcdef", 1);
	return (siz);
}
