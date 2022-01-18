/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 12:37:57 by sdalton           #+#    #+#             */
/*   Updated: 2021/04/30 13:03:00 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Function name ft_lstadd_front									*/
/*	Prototype void ft_lstadd_front(t_list **lst, t_list *new);      */
/*	Turn in files -                                                 */
/*	Parameters #1. The address of a pointer to the first link of    */
/*	a list.                                                         */
/*	 #2. The address of a pointer to the element to be              */
/*	added to the list.                                              */
/*	Return value None                                               */
/*	External functs. None                                           */
/*	Description Adds the element ’new’ at the beginning of the      */
/*	list.                                                           */

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*head;

	head = *lst;
	*lst = new;
	new->next = head;
}
