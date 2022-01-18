/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 18:43:52 by sdalton           #+#    #+#             */
/*   Updated: 2021/04/29 20:01:58 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Function name ft_itoa												*/
/*Prototype char *ft_itoa(int n);                                   */
/*Turn in files -                                                   */
/*Parameters #1. the integer to convert.                            */
/*Return value The string representing the integer. NULL if the     */
/*allocation fails.                                                 */
/*External functs. malloc                                           */
/*Description Allocates (with malloc(3)) and returns a string       */
/*representing the integer received as an argument.                 */
/*Negative numbers must be handled.									*/

static int	get_digits(int n)
{
	size_t	dig;

	dig = 0;
	if (!n)
		return (1);
	while (n)
	{
		n /= 10;
		dig++;
	}
	return (dig);
}

char	*ft_itoa(int n)
{
	char	*s;
	size_t	s_len;
	size_t	i;
	int		sign;

	sign = (1 - 2 * (n < 0));
	s_len = get_digits(n) + (n < 0);
	s = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!s)
		return (NULL);
	s[s_len] = 0;
	if (n < 0)
		s[0] = '-';
	else if (!n)
		s[0] = '0';
	i = s_len;
	while (n)
	{
		s[i - 1] = 48 + sign * (n % 10);
		i--;
		n /= 10;
	}
	return (s);
}
/*
#include <stdio.h>
#include <string.h>

int main() //(int argc, char *argv[])
{
	printf("%s\n", ft_itoa(0));
	return (0);
}*/
