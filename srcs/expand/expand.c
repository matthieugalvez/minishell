/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:55:27 by mmanuell          #+#    #+#             */
/*   Updated: 2025/02/05 14:32:11 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*parse_expand(char *input, t_data *data,
int expand_index, int double_quote)
{
	char	**parts;
	char	*expand;

	parts = get_parts(input, &expand_index, &double_quote);
	if (!parts)
		return (NULL);
	parts[3] = NULL;
	print_linetab("During Expand", parts);
	expand = join_parts(parts, &expand_index, data);
	if (!expand)
		return (NULL);
	free(input);
	if (expand && expand[expand_index]
		&& ft_strchr(&expand[expand_index], '$'))
		return (parse_expand(expand, data, expand_index, double_quote));
	return (expand);
}

static char	**ft_expand(char **input, t_data *data, int *i)
{
	input[*i] = parse_expand(input[*i], data, 0, -1);
	if (!input[*i])
	{
		data->exit_code = 1;
		ft_kill(NULL, data);
	}
	print_linetab("After Expand", input);
	if (!(input[*i - 1] && (input[*i - 1][0] == '>'
			|| input[*i - 1][0] == '<')))
		input = split_expand_result(input, i);
	print_linetab("After Split Expand", input);
	if (!input)
	{
		data->exit_code = 1;
		ft_kill(NULL, data);
	}
	return (input);
}

char	**ft_checkexpand(char **input, t_data *data)
{
	int		i;
	char	*found_expand;

	i = 0;
	while (input[i])
	{
		if (i > 0 && !ft_strncmp(input[i - 1], "<<", ft_strlen(input[i - 1])))
			i++;
		else
		{
			found_expand = ft_strchr(input[i], '$');
			if (found_expand)
				input = ft_expand(input, data, &i);
			i++;
		}
	}
	i = 0;
	while (input[i])
	{
		if (!ft_strncmp(input[i], " ", ft_strlen(input[i])))
			ft_cut_tabline(input, i);
		i++;
	}
	return (input);
}
