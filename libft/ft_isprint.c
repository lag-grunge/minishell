/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:54:18 by sdalton           #+#    #+#             */
/*   Updated: 2021/04/26 20:16:07 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*#include <ctype.h>*/
/*	 isprint()
              checks for any printable character including space. */

int	ft_isprint(int c)
{
	return (32 <= c && c < 127);
}
