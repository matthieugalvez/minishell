/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:31:30 by mgalvez           #+#    #+#             */
/*   Updated: 2025/02/24 15:08:21 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

double	ft_atof(char *num1, char *num2)
{
	int		len_num2;
	double	integer;
	double	decimal;

	if (!num2)
		return (ft_atol(num1));
	len_num2 = 0;
	while (num2[len_num2])
		len_num2++;
	integer = (double) ft_atol(num1);
	decimal = ft_atol(num2) / pow(10, len_num2);
	if (num1[0] == '-')
		decimal *= -1;
	return (integer + decimal);
}
