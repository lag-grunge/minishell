#include "clean.h"

static void free_if_exist(void *s, void (*func)(void **))
{
	if (s)
		func(&s);
}

static void	clean_redir(void **ptr)
{
	t_redir *red;
	t_redir *tmp;

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

void clean_cmd(t_cmd *cmd)
{
	if (cmd->args)
	{
		clean_split(cmd->args, ft_spllen(cmd->args));
		cmd->args = NULL;
	}
	free_if_exist(cmd->redir, clean_redir);
	free(cmd);
}

void clean_all(t_stmnt **st)
{
	t_stmnt *stmnt;

	stmnt = *st;
	if (stmnt->type == op_sbsh)
	{
		clean_all((t_stmnt **)&stmnt->oper1);
		free_if_exist(stmnt->redir, clean_redir);
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
