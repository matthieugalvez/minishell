/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:50:30 by mmanuell          #+#    #+#             */
/*   Updated: 2025/09/10 13:28:07 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_expand_rpart(char *input, char *lpart, char *mpart)
{
	int		start;
	int		len;

	start = ft_strlen(lpart) + ft_strlen(mpart);
	len = ft_strlen(input) - start;
	if (len)
		return (ft_substr(input, start, len));
	else
		return (ft_calloc(sizeof(char), 1));
}

static char	*get_expand_mpart(char *input, int start)
{
	char	*out;
	int		i;
	int		len;

	i = start;
	len = 1;
	if (!input[i])
		return (ft_calloc(sizeof (char), 1));
	while (input[++i])
	{
		if ((input[i] == '?' || input[i] == '\"' || input[i] == '\'')
			&& input[i - 1] == '$')
			return (expand_passquotes(input, i));
		if (!ft_isalnum(input[i]) && input[i] != '_')
			break ;
		if (input[i - 1] == '$'
			&& !ft_isalpha(input[i]) && input[i] != '_')
		{
			len ++;
			break ;
		}
		len++;
	}
	out = ft_substr(input, start, len);
	return (out);
}

static char	*get_expand_lpart(char *input, int *expand_index, int *double_quote)
{
	char	*out;

	while (input[*expand_index])
	{
		if (input[*expand_index] == '\"')
			*double_quote *= -1;
		if (input[*expand_index] == '\'' && *double_quote == -1)
		{
			*expand_index += 1;
			while (input[*expand_index] && input[*expand_index] != '\'')
				*expand_index += 1;
		}
		if (input[*expand_index] == '$' && (!(*double_quote == 1
					&& input[*expand_index + 1]
					&& input[*expand_index + 1] == '\"')))
		{
			out = ft_substr(input, 0, *expand_index);
			return (out);
		}
		*expand_index += 1;
	}
	out = ft_substr(input, 0, *expand_index);
	return (out);
}

char	*join_parts(char **parts, int *expand_index,
int double_quote, t_data *data)
{
	char	*out;

	out = get_expand_value(parts[1], double_quote, data);
	if (!out)
	{
		ft_freetab(parts);
		return (NULL);
	}
	if (out && *out)
	{
		if (parts[0][0])
			out = ft_strjoin_free(parts[0], out, 2);
		*expand_index = ft_strlen(out);
		if (parts[2][0])
			out = ft_strjoin_free(out, parts[2], 1);
	}
	else
	{
		if (out)
			free(out);
		out = ft_strjoin(parts[0], parts[2]);
	}
	ft_freetab(parts);
	return (out);
}

char	**get_parts(char *input, int *expand_index, int *double_quote)
{
	char	**parts;

	parts = ft_calloc(sizeof(char *), 4);
	if (!parts)
		return (NULL);
	parts[0] = get_expand_lpart(input, expand_index, double_quote);
	if (!parts[0])
	{
		free(parts);
		return (NULL);
	}
	parts[1] = get_expand_mpart(input, ft_strlen(parts[0]));
	if (!parts[1])
	{
		ft_freetab(parts);
		return (NULL);
	}
	parts[2] = get_expand_rpart(input, parts[0], parts[1]);
	if (!parts[2])
	{
		ft_freetab(parts);
		return (NULL);
	}
	return (parts);
}
