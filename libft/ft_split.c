/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:29:01 by mgalvez           #+#    #+#             */
/*   Updated: 2024/12/28 12:54:11 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_passsep(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	return (i);
}

static int	ft_nextwordlenght(char const *s, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

static char	**ft_maketab(char const *s, char c, int words_nb, char **tab)
{
	int	i;
	int	j;
	int	word_len;

	i = 0;
	j = 0;
	while (j < words_nb)
	{
		i += ft_passsep(&s[i], c);
		word_len = ft_nextwordlenght(&s[i], c);
		tab[j] = ft_calloc(sizeof(char), (word_len + 1));
		if (!tab[j])
		{
			ft_freetab(tab);
			return (NULL);
		}
		ft_strlcpy(tab[j], &s[i], word_len + 1);
		j++;
		i += word_len;
	}
	tab[j] = NULL;
	return (tab);
}

static int	ft_countwords(char const *s, char c)
{
	int	i;
	int	nb;
	int	in_sep;

	i = 0;
	nb = 0;
	in_sep = 1;
	while (s[i])
	{
		if (s[i] == c)
			in_sep = 1;
		else
		{
			if (in_sep == 1)
				nb++;
			in_sep = 0;
		}
		i++;
	}
	return (nb);
}

char	**ft_split(char const *s, char c)
{
	int		words_nb;
	char	**tab;

	words_nb = ft_countwords(s, c);
	tab = ft_calloc(sizeof(char *), (words_nb + 1));
	if (!tab)
		return (NULL);
	return (ft_maketab(s, c, words_nb, tab));
}
