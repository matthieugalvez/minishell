/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:54:01 by mgalvez           #+#    #+#             */
/*   Updated: 2024/11/13 17:04:04 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	i;

	i = ft_strlen(s1) + ft_strlen(s2);
	dst = malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, i + 1);
	ft_strlcat(dst, s2, i + 1);
	return (dst);
}
