/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_fd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:17:57 by mgalvez           #+#    #+#             */
/*   Updated: 2025/02/05 18:16:28 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*make_newfilename(char **filename_tab)
{
	char	*new_filename;

	new_filename = ft_strdup(filename_tab[0]);
	ft_freetab(filename_tab);
	if (!new_filename)
	{
		ft_putstr("Error\nFailed to init string\n", 2);
		return (NULL);
	}
	return (new_filename);
}

char	*unquote_filename(char *filename)
{
	char	**filename_tab;

	filename_tab = ft_calloc(sizeof(char *), 2);
	if (!filename_tab)
	{
		ft_putstr("Error\nFailed to init tab\n", 2);
		return (NULL);
	}
	filename_tab[0] = ft_strdup(filename);
	if (!filename_tab[0])
	{
		ft_putstr("Error\nFailed to init string\n", 2);
		free(filename_tab);
		return (NULL);
	}
	ft_unquote(filename_tab);
	if (!filename_tab)
	{
		ft_putstr("Error\nFailed to unquote tab\n", 2);
		return (NULL);
	}
	return (make_newfilename(filename_tab));
}
