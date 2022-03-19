/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:44:47 by sdalton           #+#    #+#             */
/*   Updated: 2022/03/19 19:42:10 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** searches for the last occurrence of the character c (an unsigned char) 
 * in the string pointed to, by the argument str.
 **/

char	*ft_strrchr(const char *str, int c)
{
	size_t			str_len;
	unsigned char	cu;
	char			*end;

	str_len = ft_strlen(str);
	cu = (unsigned char)c;
	if (!cu)
		return ((char *)str + str_len);
	end = (char *)str + str_len;
	while (end > str)
	{
		end--;
		if ((unsigned char)*end == cu)
			return (end);
	}	
	return (NULL);
}
