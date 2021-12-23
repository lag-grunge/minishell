#include "minishell.h"

void print_stmnt(t_stmnt *stmnt, char *pos)
{
	char *tmp;

	if (!pos)
	{
		printf("pos of statement root");
		pos = ft_strdup("");
	}
	else
		printf("pos of statement %s", pos);
	if (stmnt->type != op_smpl) {
		if (stmnt->type == op_or)
			printf("type OR\n");
		else if (stmnt->type == op_and)
			printf("type AND\n");
		else if (stmnt->type == op_sbsh)
			printf("type SBSH\n");
	}
	if (stmnt->oper1)
	{
		tmp = pos;
	}


}