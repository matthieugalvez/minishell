/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_spliter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:18:07 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/28 13:58:54 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	operator_lenght(char const *s)
{
	int	i;

	i = 0;
	if (s[i] == '|')
		return (i++);
	while (s[i] && (s[i] == '<' || s[i] == '>'))
		i++;
	return (i);
}

static int	passquote(char const *s)
{
	int		i;
	char	quote;

	i = 0;
	while (s[i] && (s[i] == '\'' || s[i] == '\"'))
	{
		quote = s[i];
		i++;
		while (s[i] && s[i] != quote)
			i++;
		if (!s[i])
			return (INT_MIN);
		i++;
	}
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
		i = passquote(&s[i]);
		if (i < 0)
			return (i);
		if (s[i] && (s[i] == '<' || s[i] == '>' || s[i] == '|') && in_word == 0)
			return (operator_lenght(&s[i]));
		else if (!s[i] || ft_isspace(s[i])
			|| s[i] == '<' || s[i] == '>' || s[i] == '|')
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

char	**ft_line_spliter(char const *s)
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
		if (i < 0)
		{
			ft_putstr("minishell: syntax error unclosed quote\n", 2);
			return (NULL);
		}
	}
	tab = ft_calloc(sizeof(char *), (words_nb + 1));
	if (!tab)
		return (NULL);
	return (make_tab(s, words_nb, tab));
}
