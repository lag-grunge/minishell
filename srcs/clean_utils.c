/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 13:00:43 by sdalton           #+#    #+#             */
/*   Updated: 2022/03/19 13:00:44 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clean.h"

void	del_env_one(t_env *tmp)
{
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

void	clean_env_hash(t_env *env_start)
{
	t_env	*cur;
	t_env	*tmp;

	cur = env_start;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

static void	clean_redir(void **ptr)
{
	t_redir	*red;
	t_redir	*tmp;

	red = *ptr;
	while (red)
	{
		tmp = red;
		red = red->next;
		free(tmp->word);
		free(tmp);
	}
	*ptr = NULL;
}

void	clean_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->args)
		ft_lstclear(&cmd->args, free);
	if (cmd->redir)
		clean_redir((void **)&cmd->redir);
	free(cmd);
}

void	clean_all(t_stmnt **st)
{
	t_stmnt	*stmnt;

	stmnt = *st;
	if (!stmnt)
		return ;
	if (stmnt->type == op_sbsh)
	{
		clean_all((t_stmnt **)&stmnt->oper1);
		if (stmnt->redir)
			clean_redir((void **)&stmnt->redir);
	}
	else if (stmnt->type == op_or || stmnt->type == op_and)
	{
		clean_all((t_stmnt **)&stmnt->oper1);
		clean_all((t_stmnt **)&stmnt->oper2);
	}
	else if (stmnt->type == op_smpl)
		clean_cmd(stmnt->oper1);
	if (stmnt->next_stmnt)
		clean_all((t_stmnt **)&stmnt->next_stmnt);
	free(stmnt);
	*st = NULL;
}
