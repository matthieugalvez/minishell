/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:33:36 by mgalvez           #+#    #+#             */
/*   Updated: 2024/11/27 15:22:13 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *elem)
{
	t_list	*lstlast;

	lstlast = ft_lstlast(*lst);
	if (!lstlast)
		*lst = elem;
	else
		lstlast->next = elem;
}
