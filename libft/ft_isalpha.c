/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:07:40 by sdalton           #+#    #+#             */
/*   Updated: 2021/04/26 20:09:14 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	#include <ctype.h>
 isalpha()
              checks for an alphabetic character; in the standard "C"
		  locale, it is equivalent to (isupper(c) || islower(c)).
		  p> " 'Q' in normal mode enters Ex mode. You almost never want this.''"
*/

static int	ft_islower(int c)
{
	return ('a' <= c && c <= 'z');
}

static int	ft_isupper(int c)
{
	return ('A' <= c && c <= 'Z');
}

int	ft_isalpha(int c)
{
	return (ft_islower(c) || ft_isupper(c));
}
