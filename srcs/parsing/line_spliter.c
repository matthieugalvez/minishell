/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_spliter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:18:07 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/27 11:43:59 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_passsep(char const *s)
{
	int	i;

	i = 0;
	while (s[i] && (!ft_isspace(s[i]) || s[i] == '<' || s[i] == '>'))
		i++;
	return (i);
}

static int	ft_nextwordlenght(char const *s)
{
	int		i;
	char	quote;

	i = 0;
	while (s[i])
	{
		while (s[i] == '\'' || s[i] == '\"')
		{
			quote = s[i];
			i++;
			while (s[i] != quote)
				i++;
		}
		if (!ft_isspace(s[i]) || s[i] == '<' || s[i] == '>')
			return (i);
		i++;
	}
	return (i);
}

static char	**ft_maketab(char const *s, int words_nb, char **tab)
{
	int	i;
	int	j;
	int	word_len;

	i = 0;
	j = 0;
	while (j < words_nb)
	{
		i += ft_passsep(&s[i]);
		word_len = ft_nextwordlenght(&s[i]);
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

static int	ft_countwords(char const *s)
{
	int		i;
	int		nb;
	int		in_sep;

	i = 0;
	nb = 0;
	in_sep = 1;
	while (s[i])
	{
		ft_passsep(&s[i]);
		if (s[i])
			nb++;
		i = ft_nextwordlenght(&s[i]);
	}
	return (nb);
}

char	**ft_line_spliter(char const *s)
{
	int		words_nb;
	char	**tab;

	words_nb = ft_countwords(s);
	tab = ft_calloc(sizeof(char *), (words_nb + 1));
	if (!tab)
		return (NULL);
	return (ft_maketab(s, words_nb, tab));
}
