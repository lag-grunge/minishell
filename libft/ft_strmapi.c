/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 11:37:47 by sdalton           #+#    #+#             */
/*   Updated: 2021/05/04 11:24:26 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*		Function name ft_strmapi											*/
/*		Prototype char *ft_strmapi(char const *s, char (*f)(unsigned        */
/*		int, char));                                                        */
/*		Turn in files -                                                     */
/*		Parameters #1. The string on which to iterate.                    	*/
/*		#2. The function to apply to each character.                      	*/
/*		Return value The string created from the successive applications  	*/
/*		of ’f’. Returns NULL if the allocation fails.                     	*/
/*		External functs. malloc                                           	*/
/*		Description Applies the function ’f’ to each character of the     	*/
/*		string ’s’ to create a new string (with malloc(3))                  */
/*		resulting from successive applications of ’f’.                      */

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	s_len;
	char			*s_map;

	i = 0;
	s_len = ft_strlen(s);
	s_map = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!s_map)
		return (NULL);
	s_map[s_len] = 0;
	while (i < s_len)
	{
		s_map[i] = f(i, s[i]);
		i++;
	}
	return (s_map);
}
