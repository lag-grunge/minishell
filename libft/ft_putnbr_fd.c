/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 09:42:21 by sdalton           #+#    #+#             */
/*   Updated: 2021/05/04 11:25:35 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Function name ft_putnbr_fd 								*/
/*	Prototype void ft_putnbr_fd(int n, int fd); 			*/
/*	Turn in files - 										*/
/*	Parameters #1. The integer to output. 					*/
/*	#2. The file descriptor on which to write. 				*/
/*	Return value None 										*/
/*	External functs. write 									*/
/*	Description Outputs the integer ’n’ to the given file 	*/
/*	descriptor. 											*/

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n < 10)
	{
		c = 48 + n;
		ft_putchar_fd(c, fd);
		return ;
	}
	else
	{
		c = 48 + (n % 10);
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(c, fd);
	}
}
