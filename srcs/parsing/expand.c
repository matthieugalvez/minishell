/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:55:27 by mmanuell          #+#    #+#             */
/*   Updated: 2025/02/03 15:09:09 by mmanuell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*parse_expand(char *input, t_data *data, int expand_index)
{
	char	**parts;
	char	*expand;

	parts = get_parts(input, expand_index);
	if (!parts)
		return (NULL);
	parts[3] = ft_calloc(1, sizeof(char));
	if (!parts[3])
	{
		ft_freetab(parts);
		return (NULL);
	}
	expand = join_parts(parts, &expand_index, data);
	if (!expand)
		return (NULL);
	free(input);
	if (expand && expand[expand_index] && ft_strchr(&expand[expand_index], '$'))
		return (parse_expand(expand, data, 1));
	return (expand);
}

void	ft_expand(char **input, t_data *data)
{
	int		i;
	char	*found_expand;

	i = 0;
	while (input[i])
	{
		found_expand = ft_strchr(input[i], '$');
		if (found_expand)
		{
			input[i] = parse_expand(input[i], data, 0);
			if (!input[i])
			{
				data->exit_code = 1;
				ft_kill(NULL, data);
			}
		}
		i ++;
	}
	i = 0;
	while (input[i])
	{
		if (!ft_strncmp(input[i], " ", ft_strlen(input[i])))
			ft_cut_tabline(input, i);
		i++;
	}
}
