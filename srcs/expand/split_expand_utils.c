/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:15:24 by mmanuell          #+#    #+#             */
/*   Updated: 2025/02/05 12:44:13 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	operator_lenght(char const *s)
{
	int		i;
	int		operator_type;

	i = 0;
	operator_type = ft_isoperator(s[i]);
	while (s[i] && (ft_isoperator(s[i]) == operator_type))
		i++;
	return (i);
}

static int	passquote(char const *s)
{
	int		i;

	i = 0;
	if (s[i] != '\'' && s[i] != '\"')
		return (i);
	while (s[i])
		i++;
	return (i);
}

static int	nextword_lenght(char const *s)
{
	int		i;
	int		in_word;

	i = 0;
	in_word = 0;
	while (s[i])
	{
		i += passquote(&s[i]);
		if (s[i] && ft_isoperator(s[i]) && in_word == 0)
			return (operator_lenght(&s[i]));
		else if (!s[i] || ft_isspace(s[i]) || ft_isoperator(s[i]))
			return (i);
		in_word = 1;
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

char	**ft_split_quotes(char const *s)
{
	int		i;
	int		words_nb;
	char	**tab;

	i = 0;
	words_nb = 0;
	while (s[i])
	{
		while (s[i] && (ft_isspace(s[i])))
			i++;
		if (s[i])
			words_nb++;
		i += nextword_lenght(&s[i]);
	}
	tab = ft_calloc(sizeof(char *), (words_nb + 1));
	if (!tab)
		return (NULL);
	return (make_tab(s, words_nb, tab));
}
