/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 12:14:59 by sdalton           #+#    #+#             */
/*   Updated: 2021/04/26 19:41:08 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	The memccpy() function copies no more than n bytes from memory			*/
/*		area src to memory area dest, stopping when the character c is		*/
/*		found.																*/
/*																			*/
/*	If the memory areas overlap, the results are undefined.					*/
/*																			*/
/*	The memccpy() function returns a pointer to the next character in		*/
/*		dest after c, or NULL if c was not found in the first n				*/
/*		characters of src.													*/

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	cu;

	i = 0;
	cu = (unsigned char)c;
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		if (((unsigned char *)dst)[i] == cu)
			return ((void *)((char *)dst + i + 1));
		i++;
	}
	return ((void *)0);
}
