# include "parser.h"

t_opers *ft_oper_new(void)
{
	t_opers *op1;

	op1 = malloc(sizeof(t_opers) * 1);
	if (op1)
		ft_memset(op1, 0, sizeof(t_opers));
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

void add_oper(t_opers **opers, int type, char ***tokens)
{
	t_opers *new_oper;

	new_oper = ft_oper_new();
	new_oper->type = type;
	new_oper->type1 = (*opers)->type;
	new_oper->oper1 = (*opers);
	*opers = new_oper;
}
