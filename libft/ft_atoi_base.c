/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 12:54:16 by sdalton           #+#    #+#             */
/*   Updated: 2021/09/13 11:20:42 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**   The atoi() function converts the initial portion of the string
       pointed to by nptr to int.  The behavior is the same as

           strtol(nptr, NULL, 10);

       except that atoi() does not detect errors.

       The atol() and atoll() functions behave the same as atoi(),
       except that they convert the initial portion of the string to
       their return type of long or long long.
RETURN VALUE
       The converted value or 0 on error.
**/

static int	ft_prefix(char **s, char *prefix, int usgn)
{
	size_t	prefix_len;
	int		sign;
	char	*ptr;

	prefix_len = ft_strlen(prefix);
	sign = 1;
	ptr = (char *)*s;
	while ((9 <= *ptr && *ptr <= 13) || *ptr == 32)
		ptr++;
	if (*ptr == '-' || *ptr == '+')
	{
		if (usgn)
			return (0);
		sign = -2 * (*ptr == '-') + 1;
		ptr++;
	}
	if (ft_strncmp(ptr, prefix, prefix_len))
		return (0);
	ptr += prefix_len;
	while (*ptr == '0')
		ptr++;
	*s = ptr;
	return (sign);
}

static int	chck_ovflw(int sign, int prev_sum, int sum, char *c)
{
	unsigned int	usum;

	usum = sum;
	if (c && *c)
		return (1);
	if (sign)
	{
		if (usum == (unsigned)INT_MIN && sign == -1)
			return (0);
		if (usum > (unsigned)INT_MIN)
			return (1);
	}
	else
	{
		if (usum < (unsigned)prev_sum)
			return (1);
	}
	return (0);
}

static int	get_digits(long int n, size_t base_len)
{
	size_t	dig;

	dig = 0;
	if (!n)
		return (0);
	while (n)
	{
		n /= base_len;
		dig++;
	}
	return (dig);
}

int	ft_atoi_base(char *s, char *base, char *prefix, int *ovflw)
{
	int		n;
	int		sign;
	int		near_ovflw;
	size_t	base_len;
	char	*pos_base;

	sign = ft_prefix(&s, prefix, 0);
	if (!sign || !*s)
		return (0);
	n = 0;
	base_len = ft_strlen(base);
	near_ovflw = get_digits(INT_MAX, base_len) - 1;
	pos_base = ft_strchr(base, *s);
	while (*s && pos_base)
	{
		n = base_len * n + (pos_base - base);
		if (ovflw && !near_ovflw && !*ovflw)
			*ovflw = chck_ovflw(sign, 0, n, ft_strchr(base, s[1]));
		s++;
		near_ovflw--;
		pos_base = ft_strchr(base, *s);
	}
	return (sign * n);
}

unsigned int	ft_usgn_atoi_base(char *s, char *base, char *prefix, int *ovflw)
{
	unsigned int	n;
	unsigned int	prev;
	int				near_ovflw;
	size_t			base_len;
	char			*pos_base;

	n = ft_prefix(&s, prefix, 1);
	if (!n || !*s)
		return (0);
	n = 0;
	base_len = ft_strlen(base);
	near_ovflw = get_digits(UINT_MAX, base_len) - 1;
	pos_base = ft_strchr(base, *s);
	while (*s && pos_base)
	{
		n = base_len * n + (pos_base - base);
		if (ovflw && !near_ovflw && !*ovflw)
			*ovflw = chck_ovflw(0, prev, n, ft_strchr(base, s[1]));
		s++;
		near_ovflw--;
		pos_base = ft_strchr(base, *s);
		prev = n;
	}
	return (n);
}

/**/
/*#include <stdio.h>*/
/*#define BASE_16 "0123456789abcdef"*/
/*#define PREFIX_16 "0x"*/
/*#define BASE_16_B "0123456789ABCDEF"*/
/*#define PREFIX_16_B "0X"*/
/*#define BASE_10 "0123456789"*/
/*#define PREFIX_10 "\0"*/
/**/
/*int main(int argc, char *argv[])*/
/*{*/
/*int	i;*/
/*int ovflw;*/
/*long long cst[] = {INT_MAX, INT_MIN, UINT_MAX};*/
/**/
/*if (argc > 1)*/
/*{*/
/*i = 1;*/
/*printf("%d\n", argc);*/
/*while (i < argc)*/
/*{*/
/*ovflw = 0;*/
/*printf("%d ", atoi(argv[i]));*/
/*printf("%d ", ft_atoi_base(argv[i], BASE_10, PREFIX_10, &ovflw));*/
/*printf("%d ", ft_atoi_base(argv[i], BASE_16, PREFIX_16, &ovflw));*/
/*if (ovflw)*/
/*{*/
/*ft_putstr_fd("Overflow1! ", 2);*/
/*ft_putstr_fd(argv[i], 2);*/
/*ft_putchar_fd('\n', 2);*/
/*}*/
/*ovflw = 0;*/
/*printf("%u\n", ft_usgn_atoi_base(argv[i], BASE_16, PREFIX_16, &ovflw));*/
/*if (ovflw)*/
/*{*/
/*ft_putstr_fd("Overflow2! ", 2);*/
/*ft_putstr_fd(argv[i], 2);*/
/*ft_putchar_fd('\n', 2);*/
/*}*/
/*i++;*/
/*}*/
/*ovflw = 0; */
/*printf("%u ", UINT_MAX);*/
/*printf("%u\n", ft_usgn_atoi_base("4294967296", BASE_10, PREFIX_10, &ovflw));*/
/*if (ovflw)*/
/*{*/
/*ft_putstr_fd("Overflow! ", 2);*/
/*ft_putstr_fd("4294967296", 2);*/
/*ft_putchar_fd('\n', 2);*/
/*}*/
/*i++;*/
/*}*/
/*else*/
/*{*/
/*size_t i = 0;*/
/*size_t N = sizeof(cst)/sizeof(*cst);*/
/*char *s;*/
/*size_t max_s = get_digits(ULONG_MAX, ft_strlen(BASE_10));*/
/*int ret;*/
/**/
/*s = (char *)malloc(max_s);*/
/*while (i < N)*/
/*{*/
/*ovflw = 0; */
/*ret = sprintf(s, "%lld", cst[i]);*/
/*s[ret] = 0;*/
/*printf("%d\n", ft_atoi_base(s, BASE_10, PREFIX_10, &ovflw));*/
/*if (ovflw)*/
/*{*/
/*ft_putstr_fd("Overflow! ", 2);*/
/*ft_putstr_fd(s, 2);*/
/*ft_putchar_fd('\n', 2);*/
/*}*/
/*ovflw = 0;*/
/*printf("%u\n", ft_usgn_atoi_base(s, BASE_10, PREFIX_10, &ovflw));*/
/*if (ovflw)*/
/*{*/
/*ft_putstr_fd("Overflow! ", 2);*/
/*ft_putstr_fd(s, 2);*/
/*ft_putchar_fd('\n', 2);*/
/*}*/
/*i++;*/
/*}*/
/**/
/*}*/
/**/
/*}*/
