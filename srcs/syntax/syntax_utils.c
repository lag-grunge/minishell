/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 13:26:20 by sdalton           #+#    #+#             */
/*   Updated: 2022/03/19 13:26:21 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

t_token	type(char *cur)
{
	int	ret;

	ret = ft_isoperator(cur);
	if (ret >= ct_ltlt && ret <= ct_egtgt)
		return (lg);
	else if (ret == ct_or || ret == ct_and)
		return (op);
	else if (ret == ct_pip)
		return (pp);
	else if (ret == ct_lbr)
		return (lb);
	else if (ret == ct_rbr)
		return (rb);
	else
		return (wrd);
}

int	expect(t_token t, char ***cur, char *module)
{
	if (accept(t, cur))
		return (0);
	return (syntax_error(syntax_err, **cur, module));
}

char	*ft_name(char *start)
{
	if (!ft_isalpha(*start) && *start != '_')
		return (start);
	while (ft_isalnum(*start) || *start == '_')
		start++;
	return (start);
}

int	accept(t_token t, char ***cur)
{
	if (**cur && t == type(**cur))
	{
		*cur += 1;
		return (1);
	}
	return (0);
}
