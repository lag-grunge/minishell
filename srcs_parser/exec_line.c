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
		return (malloc_err);
	ft_parser(&stmnt, tokens, tokens + ft_spllen(tokens) - 1);
//	exec_stmnt(stmnt);
	return (1);
}

int main(int argc, char *argv[])
{
	exec_line(argv[1]);
	return (0);
}
