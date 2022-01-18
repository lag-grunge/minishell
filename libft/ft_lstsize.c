/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 13:15:23 by sdalton           #+#    #+#             */
/*   Updated: 2021/05/04 11:26:38 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Function name ft_lstsize									*/
/*	Prototype int ft_lstsize(t_list *lst);                      */
/*	Turn in files -                                             */
/*	Parameters #1. The beginning of the list.                   */
/*	Return value Length of the list.                            */
/*	External functs. None                                       */
/*	Description Counts the number of elements in a list.        */

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*next;

	i = 0;
	next = lst;
	while (next)
	{
		next = next->next;
		i++;
	}
	return (i);
}
