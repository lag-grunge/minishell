/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:36:05 by sdalton           #+#    #+#             */
/*   Updated: 2021/05/04 14:28:52 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Function name ft_lstclear
	Prototype void ft_lstclear(t_list **lst, void (*del)(void
	*));
	Turn in files -
	Parameters #1. The adress of a pointer to an element.
	 #2. The adress of the function used to delete the
	content of the element.
	Return value None
	External functs. free
	Description Deletes and frees the given element and every
	successor of that element, using the function ’del’
	and free(3).
	Finally, the pointer to the list must be set to
	NULL.														*/

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cur;

	cur = *lst;
	while (cur)
	{
		*lst = cur->next;
		ft_lstdelone(cur, del);
		cur = *lst;
	}
}
