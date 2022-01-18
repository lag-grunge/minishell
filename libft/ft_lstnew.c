/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 12:17:34 by sdalton           #+#    #+#             */
/*   Updated: 2021/05/04 11:27:21 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	  Function name ft_lstnew										*/
/*	  Prototype t_list *ft_lstnew(void *content);                   */
/*	  Turn in files -                                               */
/*	  Parameters #1. The content to create the new element with.	*/
/*	  Return value The new element.                                 */
/*	  External functs. malloc                                       */
/*	  Description Allocates (with malloc(3)) and returns a new      */
/*	  element. The variable ’content’ is initialized                */
/*	  with the value of the parameter ’content’. The                */
/*	  variable ’next’ is initialized to NULL.                       */

t_list	*ft_lstnew(void *content)
{
	t_list	*new_list;

	new_list = (t_list *)malloc(sizeof(t_list));
	if (!new_list)
		return (NULL);
	new_list->content = content;
	new_list->next = NULL;
	return (new_list);
}
