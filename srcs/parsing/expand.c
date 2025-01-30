/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:55:27 by mmanuell          #+#    #+#             */
/*   Updated: 2025/01/30 18:04:18 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_expand_lpart(char *input)
{
	int		expand_index;
	int		double_quote;

	double_quote = -1;
	expand_index = 0;
	while (input[expand_index])
	{
		if (input[expand_index] == '\"')
			double_quote *= -1;
		if (input[expand_index] == '\'' && double_quote == -1)
		{
			expand_index++;
			while (input[expand_index] && input[expand_index] != '\'')
				expand_index++;
		}
		if (input[expand_index] == '$')
			return (ft_substr(input, 0, expand_index));
		expand_index++;
	}
	return (NULL);
}

static char	*get_expand_rpart(char *input, char *lpart, char *mpart)
{
	char	*out;
	int		start;
	int		len;

	out = NULL;
	start = ft_strlen(lpart) + ft_strlen(mpart);
	len = ft_strlen(input) - start;
	if (len)
		out = ft_substr(input, start, len);
	if (!out)
		return (NULL);
	return (out);
}

static char	*get_expand_mpart(char *input, char *lpart)
{
	char	*out;
	int		start;
	int		i;
	int		len;

	start = ft_strlen(lpart);
	i = start + 1;
	len = 1;
	out = NULL;
	while (input[i])
	{
		if (!ft_isalnum(input[i]) && input[i] != '_')
			break ;
		i++;
		len++;
	}
	if (len)
		out = ft_substr(input, start, len);
	if (!out)
		return (NULL);
	return (out);
}

static char	*parse_expand(char *input, t_data *data)
{
	char	*expand;
	char	*lpart;
	char	*rpart;

	lpart = get_expand_lpart(input);
	if (!lpart)
		return (input);
	expand = get_expand_mpart(input, lpart);
	rpart = get_expand_rpart(input, lpart, expand);
	expand = get_env_value(expand, data);
	if (expand)
	{
		if (lpart)
			expand = ft_strjoin_free2(lpart, expand);
		if (rpart)
			expand = ft_strjoin_free(expand, rpart);
	}
	else
		expand = ft_strjoin(lpart, rpart);
	free(rpart);
	free(lpart);
	free(input);
	if (expand && ft_strchr(expand, '$'))
		return (parse_expand(expand, data));
	return (expand);
}

void	ft_expand(char **input, t_data *data)
{
	int		i;
	char	*found_expand;

	(void) data;
	i = 0;
	while (input[i])
	{
		found_expand = ft_strchr(input[i], '$');
		if (found_expand && *(found_expand + 1))
		{
			input[i] = parse_expand(input[i], data);
		}
		i ++;
	}
}
