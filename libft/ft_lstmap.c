/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 10:34:10 by sdalton           #+#    #+#             */
/*   Updated: 2021/05/04 14:28:30 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Function name ft_lstmap 												*/
/*	Prototype t_list *ft_lstmap(t_list *lst, void *(*f)(void *), 			*/
/*	void (*del)(void *)); 													*/
/*	Turn in files - 														*/
/*	Parameters #1. The adress of a pointer to an element. 					*/
/*	#2. The adress of the function used to iterate on 						*/
/*	the list. 																*/
/*	#3. The adress of the function used to delete the 						*/
/*	content of an element if needed. 										*/
/*	Return value The new list. NULL if the allocation fails. 				*/
/*	External functs. malloc, free 											*/	
/*	Description Iterates the list ’lst’ and applies the function 			*/
/*	’f’ to the content of each element. Creates a new 						*/
/*	list resulting of the successive applications of 						*/
/*	the function ’f’. The ’del’ function is used to 						*/
/*	delete the content of an element if needed. 							*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*cur;
	t_list	*res;
	t_list	*cur_r;

	cur = lst;
	res = NULL;
	while (cur)
	{
		cur_r = ft_lstnew(cur->content);
		if (!cur_r)
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		cur_r->content = f(cur_r->content);
		if (cur->content && !(cur_r->content))
			ft_lstdelone(cur_r, del);
		else
			ft_lstadd_back(&res, cur_r);
		cur = cur->next;
	}
	return (res);
}
