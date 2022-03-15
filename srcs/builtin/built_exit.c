/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fphlox <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 02:52:46 by fphlox            #+#    #+#             */
/*   Updated: 2022/03/15 02:52:48 by fphlox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "biltins.h"

static unsigned long long int	ft_atoi_numbers(const char *str)
{
	unsigned long long int	rezult;
	int						chek;

	chek = 0;
	rezult = 0;
	if ((*str > 47) && (*str < 58))
	{
		rezult = *str - 48;
		str++;
	}
	while ((*str > 47) && (*str < 58))
	{
		rezult = (rezult * 10 + (*str - 48));
		str++;
		chek++;
	}
	if (chek > 19)
		rezult = 12345678901234567890U;
	return (rezult);
}

static unsigned long long int	ft_ull_atoi(const char *str)
{
	unsigned long long int	rezult;

	while ((*str == 32) || ((*str > 8) && (*str < 14)))
		str++;
	if ((*str == 43) || (*str == 45))
		str++;
	rezult = ft_atoi_numbers(str);
	return (rezult);
}

static unsigned long long int	ft_pre_atoi(char *str, int c, int znak)
{
	unsigned long long int	i;

	i = 0;
	while ((str[i] == 32) || ((str[i] > 8) && (str[i] < 14)))
		i++;
	if ((str[i] == '+') || (str[i] == '-'))
		i++;
	while (str[i] != '\0')
	{
		if (((str[i] >= '0') && (str[i] <= '9')) || (str[i] == 0))
		{
			i++;
			c++;
		}
		else
			return (12345678901234567890U);
	}
	i = ft_ull_atoi(str);
	if (((i > 9223372036854775807U) && (znak != -1))
		|| (i > 9223372036854775808U) || (c == 0))
		return (12345678901234567890U);
	return (i);
}

static int	ft_pre_atoi_znak(char *str)
{
	unsigned long long int	i;

	i = 0;
	while ((str[i] == 32) || ((str[i] > 8) && (str[i] < 14)))
		i++;
	if (str[i] == '-')
		return (-1);
	else
		return (1);
}

int	ft_exit(t_list *orgs)
{
	unsigned long long int	num;
	int						znak;
	long long int			ret;

	write (2, "exit\n", 5);
	if (orgs == NULL)
	{
		znak = get_last_status();
		exit (znak);
	}
	znak = ft_pre_atoi_znak(orgs->content);
	num = ft_pre_atoi(orgs->content, 0, znak);
	if (num == 12345678901234567890U)
	{
		er_mes ("minishell: exit: ", (char *)orgs->content, NULL);
		write (2, ": numeric argument required\n", 28);
		exit (255);
	}
	else if (ft_lstsize(orgs) <= 1)
	{
		ret = num * znak;
		exit ((unsigned char) ret);
	}
	write (2, "minishell: exit: too many arguments\n", 36);
	return (1);
}
