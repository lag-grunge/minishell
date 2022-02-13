#include "../includes/minishell.h"
#include "exec_stmnt.h"
#include "signal_dispose.h"
#include "redirect.h"

static void child(t_stmnt *stmnt, int pdes[2])
{
	int	ret;

	signal_dispose(child_fork);
	if (stmnt->next_stmnt)
		ft_redirect(pdes, STDOUT_FILENO);
	if (stmnt->type == op_smpl)
		exec_cmd(stmnt->oper1);
	else if (stmnt->type == op_sbsh)
	{
		ret = make_all_red_exp(stmnt->redir) || ft_openfiles(stmnt->redir);
		if (ret)
			exit(1);
		exec_stmnt(stmnt->oper1, &ret, 0);
		exit(ret);
	}
}

static void parent(t_stmnt *stmnt, int pdes[2], int p, int *res)
{
	signal_dispose(parent_fork);
	if (stmnt->next_stmnt)
	{
		ft_redirect(pdes, STDIN_FILENO);
		exec_stmnt(stmnt->next_stmnt, res, ++p);
	}
	else
	{
		if (p >= 1)
			save_restore_stdin_stdount();
		*res = wait_child(p);
		signal_dispose(new_shell);
	}

}

void exec_smpl_sbsh(t_stmnt *stmnt, int p, int pdes[2], int *res)
{
	pid_t pid;

	/*if (БИЛТИН)
	{
		*res = ВЫПОЛНИТЬ ФУНКЦИЮ БИЛТИН;
		return ;
	}*/
	pid = fork();
	if (pid < 0)
		exit(fork_err);
	else if (pid == 0)
		child(stmnt, pdes);
	else
		parent(stmnt, pdes, p, res);
}

void exec_stmnt(t_stmnt *stmnt, int *res, int p)
{
	int pdes[2];

	if (stmnt->next_stmnt && pipe(pdes) == -1)
		exit (fork_err);
	if (stmnt->next_stmnt && !p)
		save_restore_stdin_stdount();
	if (stmnt->type == op_smpl || stmnt->type == op_sbsh)
		exec_smpl_sbsh(stmnt, p, pdes, res);
	else if (stmnt->type == op_or || stmnt->type == op_and)
	{
		exec_stmnt(stmnt->oper1, res, 0);
		if ((!*res && stmnt->type == op_and) || (*res && stmnt->type == op_or))
			exec_stmnt(stmnt->oper2, res, 0);
	}
}