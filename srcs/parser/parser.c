/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 13:44:54 by sdalton           #+#    #+#             */
/*   Updated: 2022/03/19 13:44:55 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/clean.h"

static int	condition(char ***cur_token, char **tokens, t_token top)
{
	if (!*cur_token)
		return (0);
	else if (type(**cur_token) == top)
		return (0);
	else if (*cur_token == tokens)
	{
		*cur_token = NULL;
		return (0);
	}
	return (1);
}

static int	ft_oper(char ***oper, char **tokens, char **lim_token, t_token top)
{
	char	**cur_token;

	cur_token = lim_token;
	while (condition(&cur_token, tokens, top))
	{
		if ((*cur_token)[0] == ')')
			cur_token = close_bracket(cur_token - 1, tokens, -1);
		else
			cur_token--;
	}
	if (cur_token && (cur_token == lim_token || cur_token == tokens))
		return (syntax_error(syntax_err, *cur_token, "minishell"));
	*oper = cur_token;
	return (0);
}

int	ft_stmnt(t_stmnt **stmnt, char **tokens, char **lim_token)
{
	char	**tpip;
	int		ret;

	ret = ft_oper(&tpip, tokens, lim_token, pp);
	if (ret)
		return (ret);
	if (!tpip)
		return (last_stmnt(stmnt, tokens, lim_token));
	if (stmnt)
	{
		ret = ft_stmnt(stmnt, tokens, tpip - 1);
		if (ret)
			return (ret);
		return (last_stmnt(stmnt, tpip + 1, lim_token));
	}
	ret = ft_stmnt(NULL, tokens, tpip - 1);
	if (ret)
		return (ret);
	return (last_stmnt(NULL, tpip + 1, lim_token));
}

int	ft_parser(t_stmnt **stmnt, char **tokens, char **lim_token)
{
	char	**oper;
	int		ret;

	ret = ft_oper(&oper, tokens, lim_token, op);
	if (ret)
		return (ret);
	if (oper)
	{
		*stmnt = ft_stmnt_new();
		if (!*stmnt)
			return (malloc_err);
		(*stmnt)->type = ((ft_isoperator(*oper) == ct_and) + op_or);
		ret = ft_parser((t_stmnt **)&(*stmnt)->oper1, tokens, oper - 1);
		if (ret)
			return (ret);
		return (ft_stmnt((t_stmnt **)&(*stmnt)->oper2, oper + 1, lim_token));
	}
	return (ft_stmnt(stmnt, tokens, lim_token));
}

int	ft_preparser(char **tokens, char **lim_token)
{
	char	**oper;
	int		ret;

	if (check_brackets(tokens, lim_token))
		return (syntax_err);
	ret = ft_oper(&oper, tokens, lim_token, op);
	if (ret)
		return (ret);
	if (oper)
	{
		ret = ft_preparser(tokens, oper - 1);
		if (ret)
			return (ret);
		return (ft_stmnt(NULL, oper + 1, lim_token));
	}
	return (ft_stmnt(NULL, tokens, lim_token));
}
