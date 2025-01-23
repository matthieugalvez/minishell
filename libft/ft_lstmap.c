/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:20:30 by mgalvez           #+#    #+#             */
/*   Updated: 2024/11/18 10:47:00 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nlst_head;
	t_list	*nlst;

	if (!lst)
		return (NULL);
	nlst_head = ft_lstnew(f(lst->content));
	if (!nlst_head)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		nlst = ft_lstnew(f(lst->content));
		if (!nlst)
		{
			ft_lstclear(&nlst_head, del);
			return (NULL);
		}
		ft_lstadd_back(&nlst_head, nlst);
		lst = lst->next;
	}
	return (nlst_head);
}
