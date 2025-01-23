/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:01:01 by mgalvez           #+#    #+#             */
/*   Updated: 2024/11/27 16:04:56 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	ft_putendl(char *s, int fd)
{
	int	i;

	if (!s)
		return (-1);
	i = ft_putstr(s, fd);
	if (i < 0)
		return (i);
	if (write(fd, "\n", 1) == 1)
		return (i + 1);
	return (-1);
}
