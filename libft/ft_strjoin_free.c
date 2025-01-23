/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:09:12 by mgalvez           #+#    #+#             */
/*   Updated: 2024/11/27 17:10:32 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*dst;
	size_t	i;

	i = ft_strlen(s1) + ft_strlen(s2);
	dst = malloc(sizeof(char) * (i + 1));
	if (!dst)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(dst, s1, i + 1);
	ft_strlcat(dst, s2, i + 1);
	free(s1);
	return (dst);
}
