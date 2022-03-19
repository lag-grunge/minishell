/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_substitution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:04:11 by sdalton           #+#    #+#             */
/*   Updated: 2022/03/19 17:04:13 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

static int	quote_num(char *value)
{
	int		q;
	char	*str;

	q = 0;
	str = value;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			q++;
		str++;
	}
	return (q);
}

static void	ft_strlcat_q(char *new_str, char *value, int prefix)
{
	int	i;

	i = prefix;
	while (*value)
	{
		if (*value == '\'')
			new_str[i] = '\"';
		if (*value == '\"')
			new_str[i] = '\'';
		if (*value == '\"' || *value == '\'')
			new_str[i + 2] = new_str[i];
		if (*value == '\"' || *value == '\'')
			new_str[i + 1] = *value;
		else
			new_str[i] = *value;
		if (*value == '\"' || *value == '\'')
			i += 3;
		else
			i++;
		value++;
	}
	new_str[i] = 0;
}

void	substitute(int *counts, char **tokens, char *value, int key_len)
{
	counts[0] = (int)ft_strlen(*tokens);
	counts[0] -= key_len;
	counts[1] = 0;
	if (value)
	{
		counts[1] = quote_num(value);
		counts[2] = (int) ft_strlen(value) + 2 * counts[1];
		counts[0] += counts[2];
	}
}

char	*make_substitution(char **tokens, char *dollar, \
								char *end_var, char *value)
{
	int		counts[3];
	char	*new_str;
	char	*ret;
	int		prefix_len;

	substitute(counts, tokens, value, (int)(end_var - dollar));
	new_str = (char *) ft_calloc((counts[0] + 1), sizeof(char));
	if (!new_str)
		exit (malloc_err);
	prefix_len = dollar - *tokens;
	ft_strlcpy(new_str, *tokens, prefix_len + 1);
	if (value && !counts[1])
		ft_strlcat(new_str, value, prefix_len + counts[2] + 1);
	else if (value)
		ft_strlcat_q(new_str, value, prefix_len);
	ret = new_str + ft_strlen(new_str);
	ft_strlcat(new_str, end_var, counts[0] + 1);
	free(*tokens);
	*tokens = new_str;
	return (ret);
}
