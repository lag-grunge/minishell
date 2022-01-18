/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:07:45 by sdalton           #+#    #+#             */
/*   Updated: 2021/04/26 13:10:43 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 	The memmove() function copies n bytes from memory area src to		*/
/*	memory area dest.  The memory areas may overlap: copying takes		*/
/*	place as though the bytes in src are first copied into a			*/
/*	temporary array that does not overlap src or dest, and the bytes	*/
/*	are then copied from the temporary array to dest. 					*/

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	int		k;
	size_t	i;

	k = (src - dst);
	i = 0;
	if (k == 0)
		return ((void *)src);
	if (k > 0)
		ft_memcpy(dst, src, n);
	else
	{
		while (i < n)
		{
			((char *)dst)[n - 1 - i] = ((char *)src)[n - 1 - i];
			i++;
		}
	}
	return (dst);
}
