/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 15:00:32 by sdalton           #+#    #+#             */
/*   Updated: 2021/05/04 11:23:51 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Function name ft_strtrim										*/
/*Prototype char *ft_strtrim(char const *s1, char const *set);	*/
/*Turn in files -												*/
/*Parameters #1. The string to be trimmed.						*/
/*#2. The reference set of characters to trim.					*/
/*Return value The trimmed string. NULL if the allocation fails.*/
/*External functs. malloc										*/
/*Description Allocates (with malloc(3)) and returns a copy of	*/
/*’s1’ with the characters specified in ’set’ removed			*/
/*from the beginning and the end of the string.					*/

static int	is_trim(char const *set, int c)
{
	size_t			i;
	unsigned char	cu;

	i = 0;
	cu = c;
	while (set[i])
	{
		if (((unsigned char *)set)[i] == cu)
			return (1);
		i++;
	}
	return (0);
}

static size_t	start_string(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (is_trim(set, s1[i]))
		i++;
	return (i);
}

static size_t	end_string(char const *s1, char const *set, size_t start)
{
	size_t	i;

	i = ft_strlen(s1) - 1;
	while (i >= start && is_trim(set, s1[i]))
		i--;
	return (i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ts;
	size_t	start;
	size_t	end;

	start = start_string(s1, set);
	end = end_string(s1, set, start);
	ts = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!ts)
		return (NULL);
	ft_strlcpy(ts, s1 + start, end - start + 1);
	return (ts);
}
