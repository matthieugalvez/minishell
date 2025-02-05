/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:05:32 by mmanuell          #+#    #+#             */
/*   Updated: 2025/02/05 15:20:02 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	merge_array(char **output, char **input, int *start)
{
	int	j;

	j = 0;
	while (input[j])
	{
		output[*start] = ft_strdup(input[j]);
		if (!output[*start])
		{
			ft_freentab(output, *start);
			return (EXIT_FAILURE);
		}
		j++;
		*start += 1;
	}
	return (EXIT_SUCCESS);
}

static char	**insert_split_result(char **input, char **expand,
int *index, char **output)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < *index)
	{
		output[j] = ft_strdup(input[i]);
		if (!output[j])
		{
			ft_freentab(output, i);
			return (NULL);
		}
		j++;
		i++;
	}
	if (merge_array(output, expand, &j))
		return (NULL);
	*index = j - 1;
	if (input[i + 1] && merge_array(output, &input[i + 1], &j))
		return (NULL);
	output[j] = NULL;
	return (output);
}

static char	**init_expand_tab(char **input, char **split_expand, int *index)
{
	int		split_len;
	int		input_len;
	char	**output;

	split_len = 0;
	input_len = 0;
	if (!input[*index][0])
		return (input);
	while (*(split_expand + split_len))
		split_len ++;
	while (*(input + input_len))
		input_len ++;
	if (split_len == 1)
	{
		ft_freetab(split_expand);
		return (input);
	}
	output = ft_calloc(split_len + input_len + 1, sizeof(char *));
	return (output);
}

static char	**quote_operators(char **split_expand)
{
	int		i;
	char	*quoted_string;

	i = 0;
	while (split_expand[i])
	{
		if (ft_isoperator(split_expand[i][0]))
		{
			quoted_string = ft_strjoin("\"", split_expand[i]);
			if (!quoted_string)
				return (NULL);
			quoted_string = ft_strjoin_free(quoted_string, "\"");
			if (!quoted_string)
				return (NULL);
			free(split_expand[i]);
			split_expand[i] = quoted_string;
		}
		i++;
	}
	return (split_expand);
}

char	**split_expand_result(char **input, int *index)
{
	char	**output;
	char	**split_expand;

	if (!ft_strncmp(input[*index], " ", ft_strlen(input[*index])))
		return (input);
	split_expand = ft_split_quotes(input[*index]);
	if (!split_expand)
		return (NULL);
	split_expand = quote_operators(split_expand);
	if (!split_expand)
		return (NULL);
	output = init_expand_tab(input, split_expand, index);
	if (!output)
		return (NULL);
	if (output == input)
		return (input);
	output = insert_split_result(input, split_expand,
			index, output);
	ft_freetab(input);
	ft_freetab(split_expand);
	return (output);
}
