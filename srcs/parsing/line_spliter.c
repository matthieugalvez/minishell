/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_spliter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:18:07 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/29 13:19:44 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	operator_lenght(char const *s)
{
	int		i;
	char	operator;

	i = 0;
	operator = s[i];
	while (s[i] && (s[i] == operator))
		i++;
	return (i);
}

static int	passquote(char const *s, int *quote_len)
{
	int		i;
	char	quote;

	i = 0;
	*quote_len = 0;
	while (s[i] && (s[i] == '\'' || s[i] == '\"'))
	{
		*quote_len += 1;
		quote = s[i];
		i++;
		while (s[i] && s[i] != quote)
			i++;
		if (!s[i])
			return (i);
		*quote_len += 1;
		i++;
	}
	return (i);
}

static int	nextword_lenght(char const *s, int *quote_len)
{
	int		i;
	int		in_word;

	i = 0;
	in_word = 0;
	while (s[i])
	{
		i += passquote(&s[i], quote_len);
		if (*quote_len % 2 != 0)
			return (i);
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
	int	quote_len;

	i = 0;
	j = 0;
	while (j < words_nb)
	{
		while (s[i] && (ft_isspace(s[i])))
			i++;
		word_len = nextword_lenght(&s[i], &quote_len);
		tab[j] = ft_calloc(sizeof(char), (word_len + 1 - quote_len));
		if (!tab[j])
		{
			ft_freetab(tab);
			return (NULL);
		}
		ft_quoteless_strlcpy(tab[j], &s[i], word_len + 1 - quote_len);
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
	int		quote_len;

	i = 0;
	words_nb = 0;
	while (s[i])
	{
		while (s[i] && (ft_isspace(s[i])))
			i++;
		if (s[i])
			words_nb++;
		i += nextword_lenght(&s[i], &quote_len);
		if (quote_len % 2 != 0)
		{
			ft_putstr("minishell: syntax error unclosed quote\n", 2);
			tab = ft_calloc(sizeof(char *), 1);
			return (tab);
		}
	}
	tab = ft_calloc(sizeof(char *), (words_nb + 1));
	if (!tab)
		return (NULL);
	return (make_tab(s, words_nb, tab));
}
