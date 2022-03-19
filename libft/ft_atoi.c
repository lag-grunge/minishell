/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:25:59 by sdalton           #+#    #+#             */
/*   Updated: 2022/03/19 19:28:32 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(char *s)
{
	long long int	n;
	int				sign;

	n = 0;
	sign = 1;
	while (ft_isspace(*s))
		s++;
	if (*s != '-' && *s != '+' && !ft_isdigit(*s))
		return (0);
	else if (*s == '+' || *s == '-')
		sign = -2 * (*s++ == '-') + 1;
	while (*s == '0')
		s++;
	while (ft_isdigit(*s))
	{
		if (10 * n + *s - 48 < n)
			return ((sign == -1) * 0 + (sign == 1) * -1);
		n = 10 * n + *s - 48;
		s++;
	}
	n = n * sign;
	return (n);
}
