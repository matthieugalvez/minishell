/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_makernguint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:52:57 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/05 12:05:36 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

int	ft_makernguint(int mod)
{
	int				fd;
	unsigned int	num;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (0);
	read(fd, &num, sizeof(unsigned int));
	close(fd);
	return (num % mod);
}
