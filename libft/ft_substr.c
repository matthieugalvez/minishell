/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:37:55 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/30 17:06:04 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;
	size_t	dst_siz;

	if (ft_strlen(s) <= start || len == 0)
	{
		dst = ft_calloc(sizeof(char), 1);
		if (!dst)
			return (NULL);
		dst[0] = '\0';
		return (dst);
	}
	i = ft_strlen(&s[start]);
	if (i < len)
		dst_siz = i + 1;
	else
		dst_siz = len + 1;
	dst = ft_calloc(sizeof(char), dst_siz);
	if (!dst)
		return (NULL);
	ft_memcpy(dst, &s[start], dst_siz - 1);
	dst[dst_siz - 1] = '\0';
	return (dst);
}
