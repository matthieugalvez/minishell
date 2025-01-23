/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:50:41 by mgalvez           #+#    #+#             */
/*   Updated: 2024/11/27 15:40:04 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

static int	ft_checktrim(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_mkstr(char const *s1, char const *set, char *buff, int buff_siz)
{
	int	i;
	int	j;

	i = 0;
	while (ft_checktrim(s1[i], set) == 1)
		i++;
	j = 0;
	while (j < buff_siz)
	{
		buff[j] = s1[i];
		j++;
		i++;
	}
	buff[j] = '\0';
	return (buff);
}

static int	ft_rcountsize(char const *s1, char const *set, int nb)
{
	int	i;
	int	j;

	i = ft_strlen(s1) - 1;
	j = 0;
	while (set[j] && i >= 0 && nb > 0)
	{
		if (set[j] == s1[i])
		{
			nb--;
			i--;
			j = 0;
		}
		else
			j++;
	}
	return (nb);
}

static int	ft_countsize(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	nb;

	i = 0;
	nb = ft_strlen(s1);
		j = 0;
	while (set[j] && s1[i] && nb > 0)
	{
		if (set[j] == s1[i])
		{
			nb--;
			i++;
			j = 0;
		}
		else
			j++;
	}
	return (ft_rcountsize(s1, set, nb));
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*buffer;
	int		buffer_siz;

	buffer_siz = ft_countsize(s1, set);
	if (!s1 || buffer_siz == 0)
	{
		buffer = malloc(sizeof(char));
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
		return (buffer);
	}
	buffer = malloc(sizeof(char) * (buffer_siz + 1));
	if (!buffer)
		return (NULL);
	return (ft_mkstr(s1, set, buffer, buffer_siz));
}
