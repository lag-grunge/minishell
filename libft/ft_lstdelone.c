/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 14:43:08 by sdalton           #+#    #+#             */
/*   Updated: 2021/05/04 11:42:35 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*		Function name ft_lstdelone										*/
/*		Prototype void ft_lstdelone(t_list *lst, void (*del)(void       */
/*		*));                                                            */
/*		Turn in files -                                                 */
/*		Parameters #1. The element to free.                             */
/*		 #2. The a/ddress of the function used to delete the            */
/*		content./                                                       */
/*		Return /value None                                              */
/*		Extern/al functs. free                                          */
/*		Descr/iption Takes as a parameter an element and frees the      */
/*		memo/ry of the element’s content using the function             */
/*		’de/l’ given as a parameter and free the element.				*/
/*		Th/e memory of ’next’ must not be freed.						*/

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}
