/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote_strings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:27:06 by mgalvez           #+#    #+#             */
/*   Updated: 2025/01/29 15:42:20 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	write_until_quote(char *src, char *dst, size_t *j)
{
	int		i;
	char	quote;

	i = 0;
	quote = src[i];
	i++;
	while (src[i] && src[i] != quote)
	{
		dst[*j] = src[i];
		i++;
		*j += 1;
	}
	return (i);
}

static char	*trim_quotes(char *src, char *dst, size_t siz)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[i] && j < siz)
	{
		if (src[i] == '\'' || src[i] == '\"')
			i += write_until_quote(&src[i], dst, &j);
		else
		{
			dst[j] = src[i];
			i++;
			j++;
		}
	}
	dst[j] = '\0';
	free(src);
	return (dst);
}

static int	pass_quote(char const *s)
{
	char	quote;
	int		i;

	i = 0;
	quote = s[i];
	i++;
	while (s[i] && s[i] != quote)
		i++;
	return (i);
}

static int	get_newlen(char const *s)
{
	int		i;
	int		quote_len;

	i = 0;
	quote_len = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote_len++;
			i += pass_quote(s);
			if (!s[i])
				return (i - quote_len);
			quote_len++;
		}
		else
			i++;
	}
	return (i - quote_len);
}

void	ft_unquote(char **input)
{
	int		i;
	size_t	new_len;
	char	*dst;

	i = 0;
	while (input[i])
	{
		new_len = get_newlen(input[i]);
		if (new_len != ft_strlen(input[i]))
		{
			dst = ft_calloc(sizeof(char), new_len + 1);
			if (!dst)
			{
				ft_freetab(input);
				return ;
			}
			input[i] = trim_quotes(input[i], dst, new_len);
			if (!input[i])
			{
				ft_freetab(input);
				return ;
			}
		}
		i++;
	}
}
