# include "minishell.h"
# include "parser.h"
# include "syntax.h"
# include "errors.h"


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