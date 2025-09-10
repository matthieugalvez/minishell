/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:09:12 by mgalvez           #+#    #+#             */
/*   Updated: 2025/02/10 15:34:18 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2, int to_free)
{
	char	*dst;
	size_t	i;

	i = ft_strlen(s1) + ft_strlen(s2);
	dst = ft_calloc(sizeof(char), i + 1);
	if (!dst)
	{
		if (to_free == 1 || to_free == 3)
			free(s1);
		if (to_free == 2 || to_free == 3)
			free(s2);
		return (NULL);
	}
	ft_strlcpy(dst, s1, i + 1);
	ft_strlcat(dst, s2, i + 1);
	if (to_free == 1 || to_free == 3)
		free(s1);
	if (to_free == 2 || to_free == 3)
		free(s2);
	return (dst);
}
