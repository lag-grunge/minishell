/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:01:05 by sdalton           #+#    #+#             */
/*   Updated: 2021/04/26 20:17:22 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*  #include <ctype.h>

       int toupper(int c);
       int tolower(int c);
       These functions convert lowercase letters to uppercase, and vice
       versa.

       If c is a lowercase letter, toupper() returns its uppercase
       equivalent

	    The value returned is that of the converted letter, or c if the
       conversion was not possible.*/

static int	ft_islower(int c)
{
	return ('a' <= c && c <= 'z');
}

int	ft_toupper(int c)
{
	if (ft_islower(c))
		return (c + ('A' - 'a'));
	return (c);
}
