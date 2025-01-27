/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_spliter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:18:07 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/27 13:36:21 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	operator_lenght(char const *s)
{
}

static int	nextword_lenght(char const *s)
{
	int		i;
	char	quote;

	i = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == '\'' || s[i] == '\"'))
		{
			quote = s[i];
			i++;
			while (s[i] && s[i] != quote)
				i++;
		}
		if (s[i] == '<' || s[i] == '>' || s[i] == '|')
			return (operator_lenght(&s[i]));
		while (s[i] && (ft_isspace(s[i])
				|| s[i] == '<' || s[i] == '>' || s[i] == '|'))
			return (i);
		i++;
	}
	return (i);
}

static char	**make_tab(char const *s, int words_nb, char **tab)
{
	int	i;
	int	j;
	int	word_len;

	i = 0;
	j = 0;
	while (j < words_nb)
	{
		while (s[i] && (ft_isspace(s[i])))
			i++;
		word_len = nextword_lenght(&s[i]);
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

static int	count_words(char const *s)
{
	int		i;
	int		nb;
	int		in_sep;

	i = 0;
	nb = 0;
	in_sep = 1;
	while (s[i])
	{
		while (s[i] && (ft_isspace(s[i])))
			i++;
		if (s[i])
			nb++;
		i += nextword_lenght(&s[i]);
	}
	return (nb);
}

char	**ft_line_spliter(char const *s)
{
	int		words_nb;
	char	**tab;

	words_nb = count_words(s);
	tab = ft_calloc(sizeof(char *), (words_nb + 1));
	if (!tab)
		return (NULL);
	return (make_tab(s, words_nb, tab));
}
