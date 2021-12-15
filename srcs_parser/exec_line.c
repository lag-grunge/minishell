# include "minishell.h"
# include "parser.h"
# include "syntax.h"
# include "errors.h"


int exec_stmnt(t_stmnt *stmnt)
{
	t_tstmnt	type;

	type = stmnt->type;
	if (type == op_none)
		return (0);
	else if (type == op_smpl)
		return (exec_cmd(stmnt->oper1));
	else if (type == op_or)
		return (exec_stmnt(stmnt->oper1) || exec_stmnt(stmnt->oper2));
	else if (type == op_and)
		return (exec_stmnt(stmnt->oper1) || exec_stmnt(stmnt->oper2));
}


int exec_line(char *read_line)
{
	char		**tokens;
	t_stmnt 	*stmnt;
	int			ret;

	stmnt = NULL;
	tokens = NULL;
	tokens = get_tokens(read_line);
	if (!tokens)
		exit (malloc_error);
	ft_parser(&stmnt, tokens);
	exec_stmnt(stmnt);
}
