#include "../includes/minishell.h"
#include "exec_stmnt.h"

static void open_pipes(t_stmnt *stmnt, int p, int h_doc[2], int pdes[2])
{
	if (stmnt->next_stmnt && pipe(pdes) == -1)
		exit (fork_err);
	if (stmnt->next_stmnt && !p)
		save_restore_stdin_stdount();
	if (stmnt->h_doc && pipe(h_doc) == -1)
		exit (fork_err);
}

static int exec_stmnt_or_and(t_stmnt *stmnt)
{
	int	ret;

	ret = exec_stmnt(stmnt->oper1, 0);
	if ((!ret && stmnt->type == op_and) || (ret && stmnt->type == op_or))
		ret = exec_stmnt(stmnt->oper2, 0);
	return (ret);
}

int exec_stmnt(t_stmnt *stmnt, int p)
{
	int pdes[2];
	int h_doc[2];

	open_pipes(stmnt, p, h_doc, pdes);
	if (stmnt->type == op_smpl || stmnt->type == op_sbsh)
		return (exec_smpl_sbsh(stmnt, p, h_doc, pdes));
	else
		return (exec_stmnt_or_and(stmnt));
}