/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 13:53:25 by sdalton           #+#    #+#             */
/*   Updated: 2022/03/19 13:53:27 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_stmnt	*ft_stmnt_new(void)
{
	t_stmnt	*stmnt;

	stmnt = malloc(sizeof(t_stmnt) * 1);
	stmnt->type = 0;
	stmnt->oper1 = NULL;
	stmnt->oper2 = NULL;
	stmnt->redir = NULL;
	stmnt->pid = 0;
	stmnt->next_stmnt = NULL;
	return (stmnt);
}

int	last_stmnt(t_stmnt **stmnt, char **tokens, char **lim_token)
{
	t_stmnt	**last;

	last = stmnt;
	if (last)
	{
		while (*last)
			last = &(*last)->next_stmnt;
		*last = ft_stmnt_new();
		if (!*last)
			exit(malloc_err);
	}
	return (ft_cmd(last, tokens, lim_token));
}
