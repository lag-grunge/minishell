/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 14:42:14 by sdalton           #+#    #+#             */
/*   Updated: 2022/03/19 19:30:07 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
