/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:16:46 by mgalvez           #+#    #+#             */
/*   Updated: 2024/12/11 10:17:50 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	ft_checklim(char *str)
{
	long	l;

	l = ft_atol(str);
	if (l > 0)
	{
		if (l > INT_MAX)
			return (1);
	}
	if (l < 0)
	{
		if (l < INT_MIN)
			return (1);
	}
	return (0);
}

int	ft_isint(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (ft_strlen(&str[i]) > 10)
		return (1);
	if (ft_strlen(&str[i]) == 10)
	{
		if (ft_checklim(str) == 1)
			return (1);
	}
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
