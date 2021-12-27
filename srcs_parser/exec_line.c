# include "minishell.h"
# include "parser.h"
# include "syntax.h"

void print_stmnt(t_stmnt *stmnt, char *pos);

int exec_line(char *read_line)
{
	char		**tokens;
	char		**lim_token;
	t_stmnt 	*stmnt;
	int			ret;

	stmnt = NULL;
	tokens = NULL;
	ret = 0;
	tokens = get_tokens(read_line, &ret);
	if (!tokens)
	{
		if (!ret)
			return (malloc_err);
		return (0);
	}
	lim_token = tokens + ft_spllen(tokens) - 1;
	ret = ft_parser(&stmnt, tokens, lim_token);
	if (ret)
		return (ret);
	print_stmnt(stmnt, NULL);
//	exec_stmnt(stmnt);
	return (0);
}

int main(int argc, char *argv[])
{
	exec_line(argv[1]);
	return (0);
}
