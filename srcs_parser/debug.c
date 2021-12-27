#include "minishell.h"

void print_args(t_cmd *cmd) {
	char **args = cmd->args;
	printf("type simple command \n");
	while (*args) {
		printf("%s\n", *args);
		args++;
	}
}
void print_pos(char *pos)
{
	if (!pos)
		printf("pos of statement root\n");
	else
		printf("pos of statement %s\n", pos);
}

void print_type(t_stmnt *stmnt)
{
	if (stmnt->type == op_smpl)
		printf("type SMPL\n");
	if (stmnt->type == op_or)
		printf("type OR\n");
	else if (stmnt->type == op_and)
		printf("type AND\n");
	else if (stmnt->type == op_sbsh)
		printf("type SBSH\n");
}

char redir_type_to_char(t_tred red)
{
	static int i;

	if (red == red_rifile)
		return ('<' * (i == 0));
	else if (red == red_rh_doc)
		return ('<');
	else if (red == red_wofile)
		return ('>' * (i == 0));
	else if (red == red_aofile)
		return ('>');
	i = (i + 1) % 2;
}

void print_redir(t_stmnt *stmnt, int sbsh)
{
	int i;
	char c1;
	char c2;
	if (sbsh)
		printf("common subshell redirect ");
	i = 1;
	while (stmnt->redir)
	{
		printf("%d ", i);
		c1 = redir_type_to_char(stmnt->redir->type);
		c2 = redir_type_to_char(stmnt->redir->type);
		printf("%c%c", c1, c2);
		printf(" %s", stmnt->redir->word);
		stmnt->redir = stmnt->redir->next;
		i++;
	}
	printf("\n");
}

void print_stmnt(t_stmnt *stmnt, char *pos);

void move(t_stmnt *stmnt, char *pos)
{
	char *tmp;
	tmp = pos;
	if (stmnt->type == op_sbsh)
	{
		pos = ft_strjoin(tmp, "s");
		free(tmp);
		print_redir(stmnt, 1);
		print_stmnt(stmnt->oper1, pos);
	}
	else if (stmnt->type == op_or || stmnt->type == op_and)
	{
		print_stmnt(stmnt->oper1, ft_strjoin(tmp, "l"));
		print_stmnt(stmnt->oper2, ft_strjoin(tmp, "r"));
		free(tmp);
	}
	else if (stmnt->type == op_smpl)
	{
		print_args(stmnt->oper1);
		print_redir(stmnt->oper1, 0);
		if (stmnt->next_stmnt)
			print_stmnt(stmnt->next_stmnt, ft_strjoin(tmp, "p"));
		else
			return ;
	}
}

void print_stmnt(t_stmnt *stmnt, char *pos)
{
	print_type(stmnt);
	print_pos(pos);
	if (!pos)
		pos = ft_strdup("");
	move(stmnt, pos);
}