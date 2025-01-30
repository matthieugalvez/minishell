/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:55:27 by mmanuell          #+#    #+#             */
/*   Updated: 2025/01/30 11:19:36 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_env_value(char *env_value, t_data *data)
{
	int		i;
	char	*to_find;
	int		len;

	i = 0;
	to_find = ft_strjoin_free(env_value, "=");
	len = ft_strlen(to_find);
	while (data->envp[i])
	{
		if (!ft_strncmp(to_find, data->envp[i], ft_strlen(to_find)))
		{
			free(to_find);
			return (ft_substr(data->envp[i],
					len,
					ft_strlen(data->envp[i])
					- ft_strlen(to_find)));
		}
		i++;
	}
	free(to_find);
	return (NULL);
}

static char	*get_expand_lpart(char *input)
{
	int		expand_index;
	char	*out;

	expand_index = ft_strlen(input) - ft_strlen(ft_strchr(input, '$'));
	if (expand_index > 0)
	{
		out = ft_substr(input, 0, expand_index);
		if (!out)
			return (NULL);
		return (out);
	}
	return (NULL);
}

static char	*get_expand_rpart(char *input)
{
	char	*rstr;
	char	*out;

	rstr = ft_strchr(ft_strchr(input, '$') + 1, '$');
	if (rstr)
	{
		out = ft_strdup(rstr);
		if (out)
			return (out);
	}
	return (NULL);
}

static char	*parse_expand(char *input, t_data *data)
{
	char	*expand;
	char	*lpart;
	char	*rpart;

	lpart = get_expand_lpart(input);
	rpart = get_expand_rpart(input);
	expand = ft_substr(input,
			ft_strlen(lpart) + 1,
			ft_strlen(input) - ft_strlen(rpart) - ft_strlen(lpart) - 1);
	// printf("Lpart : %s\n", lpart);
	// printf("Rpart : %s\n", rpart);
	// printf("expand : %s\n", expand);
	expand = get_env_value(expand, data);
	// printf("expand : %s\n", expand);
	if (expand)
	{
		if (lpart)
			expand = ft_strjoin_free2(lpart, expand);
		if (rpart)
			expand = ft_strjoin_free(expand, rpart);
	}
	else
	{
		expand = ft_strjoin(lpart, rpart);
	}
	free(rpart);
	free(lpart);
	free(input);
	if (expand && ft_strchr(expand, '$'))
		return (parse_expand(expand, data));
	return (expand);
}

void	ft_expand(char **input, t_data *data)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_strchr(input[i], '$'))
			input[i] = parse_expand(input[i], data);
		i ++;
	}
}
