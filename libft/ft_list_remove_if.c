/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez <mgalvez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:08:29 by mgalvez           #+#    #+#             */
/*   Updated: 2025/06/30 18:39:51 by mgalvez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include <stdlib.h>

int	cmp(t_list *lst, void *content_ref){
	if (&lst->content == &content_ref)
		return (0);
	return (1);
}

void	ft_list_remove_if(t_list **lst, void *content_ref, int (*cmp)(t_list *, void *))
{
	t_list	*current_node;
	t_list	*last_node;

	last_node = NULL;
	current_node = *lst;
	while (current_node)
	{
		if (cmp(current_node, content_ref) == 0)
		{
			last_node->next = current_node->next;
			free(current_node);
			current_node = last_node;
		}
		last_node = current_node;
		current_node = current_node->next;
	}
}

