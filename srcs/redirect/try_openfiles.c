#include "minishell.h"
#include "parser.h"
#include "redirect.h"

void try_routine(t_stmnt *stmnt)
{
	t_redir	*red;
	int 	ret;

	ret = 0;
	red = stmnt->redir;
	if (!red && stmnt->type == op_smpl)
		red = ((t_cmd *)stmnt->oper1)->redir;
	else if (!red && stmnt->type == op_sbsh)
		ret = try_openfiles(stmnt->oper1);
	else if (!red)
		ret = !(!try_openfiles(stmnt->oper1) && !try_openfiles(stmnt->oper2));
	if (ret)
		exit (no_file_exists);
	while (red)
	{
		if (red->type == red_rifile && access(red->word, F_OK) == -1)
			exit_no_file_error(no_file_exists, red->word);
		red = red->next;
	}
	exit (0);
}

int try_openfiles(t_stmnt *stmnt)
{
	int	res;
	int	status;

	res = 0;
	while (stmnt)
	{
		pid_t pid = fork();
		if (pid < 0)
			exit (fork_err);
		else if (pid == 0)
			try_routine(stmnt);
		stmnt = stmnt->next_stmnt;
		wait(&status);
		if (WIFEXITED(status))
			res |= WEXITSTATUS(status);
	}
	return (res != 0);
}
