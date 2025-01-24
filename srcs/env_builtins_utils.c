/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanuell <mmanuell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:08:25 by mmanuell          #+#    #+#             */
/*   Updated: 2025/01/24 16:08:01 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**realloc_envp(char **old_envp, size_t new_size)
{
	char	**new_envp;

	new_envp = ft_calloc((new_size + 1), sizeof (char *));
	if (!new_envp)
		return (NULL);
	if (ft_tabcpy(new_envp, old_envp) == 1)
		return (NULL);
	ft_freetab(old_envp);
	return (new_envp);
}

char	*parse_var_name(char *arg)
{
	size_t	len;

	len = 0;
	while (*(arg + len) && *(arg + len) != '=')
		len++;
	if (*arg + len)
		return (ft_substr(arg, 0, len));
	else
		return (NULL);
}

int	get_env_index(char *env_var, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->envp_len)
	{
		if (!ft_strncmp(env_var, data->envp[i], ft_strlen(env_var)))
			return (i);
		i++;
	}
	return (i);
}
