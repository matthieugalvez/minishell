/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:53:02 by mmanuell          #+#    #+#             */
/*   Updated: 2025/01/23 16:15:30 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*cp1;
	unsigned char	*cp2;

	cp1 = (unsigned char *) s1;
	cp2 = (unsigned char *) s2;
	while (*cp1 && *cp2)
	{
		if (*cp1 != *cp2)
			return (*cp1 - *cp2);
		cp1++;
		cp2++;
	}
	return (*cp1 - *cp2);
}
