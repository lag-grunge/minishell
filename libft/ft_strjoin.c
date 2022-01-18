/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 14:42:14 by sdalton           #+#    #+#             */
/*   Updated: 2021/06/24 12:53:24 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Function name ft_strjoin									*/
/*	Prototype char *ft_strjoin(char const *s1, char const *s2);	*/
/*	Turn in files -												*/
/*	Parameters #1. The prefix string.							*/
/*	#2. The suffix string.										*/
/*	Return value The new string. NULL if the allocation fails.	*/
/*	External functs. malloc										*/
/*	Description Allocates (with malloc(3)) and returns a new	*/ 	
/*	string, which is the result of the concatenation			*/ 	
/*	of ’s1’ and ’s2’.											*/ 	

char	*ft_strjoin(char const *s1, char const *s2)	
{
	char	*js;
	size_t	s1_len;
	size_t	s2_len;
	size_t	js_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	js_len = s1_len + s2_len;
	js = (char *)malloc(sizeof(char) * (js_len + 1));
	if (!js)
		return (NULL);
	ft_strlcpy(js, s1, js_len + 1);
	ft_strlcat(js, s2, js_len + 1);
	return (js);
}
/*

#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc == 3)
		printf("%s\n", ft_strjoin(argv[1], argv[2]));
}*/
