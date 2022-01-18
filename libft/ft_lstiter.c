/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 10:28:39 by sdalton           #+#    #+#             */
/*   Updated: 2021/05/04 10:33:49 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Function name ft_lstiter 										*/
/*	Prototype void ft_lstiter(t_list *lst, void (*f)(void *)); 		*/
/*	Turn in files - 												*/
/*	Parameters #1. The adress of a pointer to an element. 			*/
/*	#2. The adress of the function used to iterate on 				*/
/*	the list. 														*/
/*	Return value None 												*/
/*	External functs. None 											*/
/*	Description Iterates the list ’lst’ and applies the function 	*/
/*	’f’ to the content of each element. 							*/

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*cur;

	cur = lst;
	while (cur)
	{
		f(cur->content);
		cur = cur->next;
	}
}
