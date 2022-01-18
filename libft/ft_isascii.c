/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:35:47 by sdalton           #+#    #+#             */
/*   Updated: 2021/04/26 20:14:09 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*#include <ctype.h>*/
/*	checks whether c is a 7-bit unsigned char value that fits
              into the ASCII character set.	*/

int	ft_isascii(int c)
{
	return (0 <= c && c <= 127);
}
