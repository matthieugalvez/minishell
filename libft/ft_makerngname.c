/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_makerngname.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:18:47 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/05 11:54:44 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char	*ft_makerngname(int len)
{
	int				fd;
	int				i;
	unsigned char	*buf;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (NULL);
	buf = malloc(sizeof(char) * (len + 1));
	if (!buf)
		return (NULL);
	read(fd, buf, len);
	close(fd);
	i = 0;
	while (i < len)
	{
		buf[i] = (buf[i] % 26) + 97;
		i++;
	}
	buf[i] = '\0';
	return ((char *)buf);
}
