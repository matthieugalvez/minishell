/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:16:35 by mgalvez           #+#    #+#             */
/*   Updated: 2024/11/15 15:29:56 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		siz;

	siz = 0;
	if (lst)
		siz++;
	else
		return (0);
	while (lst->next)
	{
		siz++;
		lst = lst->next;
	}
	return (siz);
}
