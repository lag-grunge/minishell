#include "../includes/minishell.h"
#include "exec_stmnt.h"
#include "environment.h"
#include "redirect.h"
#include "signal_dispose.h"

void exec_stmnt(t_stmnt *stmnt, int *res, int p)
{
	int pdes[2];

	if (stmnt->next_stmnt && pipe(pdes) == -1)
		exit (fork_err);
	if (stmnt->next_stmnt && !p)
		save_restore_stdin_stdount();
	if (stmnt->type == op_smpl || stmnt->type == op_sbsh)
		*res = exec_smpl_sbsh(stmnt, p, pdes);
	else if (stmnt->type == op_or || stmnt->type == op_and)
	{
		exec_stmnt(stmnt->oper1, res, 0);
		if ((!*res && stmnt->type == op_and) || (*res && stmnt->type == op_or))
			exec_stmnt(stmnt->oper2, res, 0);
	}
}