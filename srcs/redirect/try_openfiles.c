#include "minishell.h"
#include "parser.h"
#include "redirect.h"

int try_openfiles(t_stmnt *stmnt)
{
	t_redir	*red;
	int 	ret;

	ret = 0;
	while (stmnt)
	{
		red = stmnt->redir;
		if (!red)
		{
			if (stmnt->type == op_smpl)
				red = ((t_cmd *)stmnt->oper1)->redir;
			else if (stmnt->type == op_sbsh)
				ret = try_openfiles(stmnt->oper1);
			else
				ret = !(!try_openfiles(stmnt->oper1) && !try_openfiles(stmnt->oper2));
			if (ret)
				return (1);
		}
		while (red) {
			if (red->type == red_rifile) {
				if (access(red->word, F_OK) == -1) {
					ft_putstr_fd("minishell: ", STDERR_FILENO);
					ft_putstr_fd(, STDERR_FILENO);
					ft_putendl_fd(": No such file or directory!", STDERR_FILENO);
					exit_no_file_error();
					return (1);
				}
			}
			red = red->next;
		}
		stmnt = stmnt->next_stmnt;
	}
	return (0);
}

int main()
{
	t_stmnt *stmnt;
	char *tokens[] = {"<", "4", "|","(" ,"<", "1", "|" , "<", "5" , "&&" , "<", "2", ")", "<", "6", "|", "<", "3", NULL};
	ft_parser(&stmnt, tokens, tokens + ft_spllen(tokens) - 1);
	printf("%d", try_openfiles(stmnt));
	return (0);
}