/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:29:24 by mgalvez           #+#    #+#             */
/*   Updated: 2025/02/01 16:29:37 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isbuiltin(char *arg)
{
	if (!ft_strncmp(arg, "echo", 5))
		return (0);
	if (!ft_strncmp(arg, "cd", 3))
		return (0);
	if (!ft_strncmp(arg, "pwd", 4))
		return (0);
	if (!ft_strncmp(arg, "export", 7))
		return (0);
	if (!ft_strncmp(arg, "unset", 6))
		return (0);
	if (!ft_strncmp(arg, "env", 4))
		return (0);
	if (!ft_strncmp(arg, "exit", 5))
		return (0);
	return (1);
}
