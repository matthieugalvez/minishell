/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:31:44 by mgalvez           #+#    #+#             */
/*   Updated: 2024/11/29 10:36:52 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	ft_putunsint(unsigned int nbr, char *base)
{
	int	siz;

	siz = 0;
	if (nbr / ft_strlen(base))
		siz += ft_putunsint(nbr / ft_strlen(base), base);
	ft_putchar(base[nbr % ft_strlen(base)], 1);
	return (siz + 1);
}
