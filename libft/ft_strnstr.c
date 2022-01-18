/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:53:43 by sdalton           #+#    #+#             */
/*   Updated: 2021/05/04 17:37:58 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/** The strnstr() function locates the	first occurrence of the	null-termi
*     nated string little in the	string big, where not more than	len characters
*     are searched.  Characters that appear after a `\0'	character are not
*     searched.	
*   RETURN VALUES
*    If	little is an empty string, big is returned; if little occurs nowhere
*    in	big, NULL is returned; otherwise a pointer to the first	character of
*     the first occurrence of little is returned.
**/

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_len;

	i = 0;
	little_len = ft_strlen(little);
	if (!(*little))
		return ((char *)big);
	while (big[i] && (i + little_len <= len))
	{
		if (!ft_memcmp(big + i, little, little_len))
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
/*
#include <string.h>
#include <stdio.h>

int main()
{

		// char *s2 = "MZIRIBMZE";
  		// size_t max = strlen(s2);
  		// char *i1 = strnstr(s1, s2, max);
  		// char *i2 = ft_strnstr(s1, s2, max);
		// printf("%d\n", i1 == i2);

		// char *s1 = "FF";
       	// char *s2 = "see FF your FF return FF now FF";
       	// char *i1 = strnstr(s1, s2, 4);
       	// char *i2 = ft_strnstr(s1, s2, 4);
		
		// char *s1 = "oh no not the empty string !";
		// char *s2 = "";
		// size_t max = 0;
		// char *i1 = strnstr(s1, s2, max);
		// char *i2 = ft_strnstr(s1, s2, max);

		char *s1 = (void *)0;
		char *s2 = "fake";
		size_t max = 0;
		char *i1 = strnstr(s1, s2, max);
		char *i2 = ft_strnstr(s1, s2, max);

       	if (i1 == i2)
        	exit(0);
       	exit(1);

		ft_strnstr("000000123", "123", 9);

		return (0);
  
}
*/
