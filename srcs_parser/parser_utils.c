# include "parser.h"

t_stmnt *ft_oper_new(void)
{
	t_stmnt *op1;

	op1 = malloc(sizeof(t_stmnt) * 1);
	if (op1)
		ft_memset(op1, 0, sizeof(t_stmnt));
	return (op1);
}

t_cmd *ft_cmd_new(void)
{
	t_cmd	*cmd1;

	cmd1 = malloc(sizeof(t_cmd) * 1);
	if (cmd1)
		ft_memset(cmd1, 0, sizeof(t_cmd));
	return (cmd1);
}

t_redir *ft_redir_new(void)
{
	t_redir	*red;

	red = malloc(sizeof(t_cmd) * 1);
	if (red)
		ft_memset(red, 0, sizeof(t_redir));
	return (red);
}



