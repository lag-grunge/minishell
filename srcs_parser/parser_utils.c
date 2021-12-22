# include "parser.h"

t_stmnt *ft_stmnt_new(void)
{
	t_stmnt *stmnt;

	stmnt = malloc(sizeof(t_stmnt) * 1);
	stmnt->type = 0;
	stmnt->oper1 = NULL;
	stmnt->oper2 = NULL;
	stmnt->redir = NULL;
	stmnt->next_stmnt = NULL;
	return (stmnt);
}

t_cmd *ft_cmd_new(void)
{
	t_cmd	*cmd1;

	cmd1 = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	cmd1->args = NULL;
	cmd1->redir = NULL;
	return (cmd1);
}

t_redir *ft_redir_new(void)
{
	t_redir	*red;

	red = malloc(sizeof(t_redir) * 1);
	red->type = 0;
	red->word = NULL;
	red->next = NULL;
	return (red);
}



