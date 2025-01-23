/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:30:07 by mgalvez           #+#    #+#             */
/*   Updated: 2024/11/13 16:34:35 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dst;
	int		siz;

	siz = ft_strlen(s) + 1;
	dst = malloc(sizeof(char) * siz);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s, siz);
	return (dst);
}
