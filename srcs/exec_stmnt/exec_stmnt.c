#include "../includes/minishell.h"
#include "exec_stmnt.h"
#include "environment.h"
#include "redirect.h"
#include "signal_dispose.h"

static void open_pipes(t_stmnt *stmnt, int p, int h_doc[2], int pdes[2])
{
	if (stmnt->next_stmnt && pipe(pdes) == -1)
		exit (fork_err);
	if (stmnt->next_stmnt && !p)
		save_restore_stdin_stdount();
	if (stmnt->h_doc && pipe(h_doc) == -1)
		exit (fork_err);
}

static void exec_stmnt_or_and(t_stmnt *stmnt, int *res)
{
	exec_stmnt(stmnt->oper1, res, 0);
	if ((!*res && stmnt->type == op_and) || (*res && stmnt->type == op_or))
		exec_stmnt(stmnt->oper2, res, 0);
}

void exec_stmnt(t_stmnt *stmnt, int *res, int p)
{
	int pdes[2];
	int h_doc[2];

	open_pipes(stmnt, p, h_doc, pdes);
	if (stmnt->type == op_smpl || stmnt->type == op_sbsh)
		*res = exec_smpl_sbsh(stmnt, p, h_doc, pdes);
	else
		exec_stmnt_or_and(stmnt, res);
}
