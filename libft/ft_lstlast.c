/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 13:22:38 by sdalton           #+#    #+#             */
/*   Updated: 2021/05/04 13:46:39 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Function name ft_lstlast								*/
/*	Prototype t_list *ft_lstlast(t_list *lst);              */
/*	Turn in files -                                         */
/*	Parameters #1. The beginning of the list.               */
/*	Return value Last element of the list.                  */
/*	External functs. None                                   */
/*	Description Returns the last element of the list.       */

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*next;
	t_list	*cur;

	cur = lst;
	if (!cur)
		return (NULL);
	next = cur->next;
	while (next)
	{
		cur = next;
		next = cur->next;
	}
	return (cur);
}
