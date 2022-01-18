/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 12:46:09 by sdalton           #+#    #+#             */
/*   Updated: 2021/04/26 16:32:52 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <ctype.h>*/

/*	int isdigit(int c);													*/
/*	The c argument is an int, the value of which the application		*/
/*	shall ensure is a character representable as an unsigned char or	*/
/*	equal to the value of the macro EOF. If the argument has any		*/
/*	other value, the behavior is undefined.								*/
/*																		*/	
/*	RETURN VALUE         												*/
/*	The isdigit() and isdigit_l() functions shall return non-zero if	*/
/*	c is a decimal digit; otherwise, they shall return 0.				*/

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}
