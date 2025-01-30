/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:54:01 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/30 14:52:15 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	i;

	i = ft_strlen(s1) + ft_strlen(s2);
	if (i == 0)
		i++;
	dst = ft_calloc(sizeof(char), i + 1);
	if (!dst)
		return (NULL);
	if (!s1 && !s2)
		dst = " ";
	else if (!s1)
		ft_strlcpy(dst, s2, i + 1);
	else if (!s2)
		ft_strlcpy(dst, s1, i + 1);
	else
	{
		ft_strlcpy(dst, s1, i + 1);
		ft_strlcat(dst, s2, i + 1);
	}
	return (dst);
}
