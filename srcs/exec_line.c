#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/syntax.h"
#include "../includes/clean.h"
#include "../includes/environment.h"

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
	ret = ft_preparser(tokens, lim_token);
	if (!ret)
		ret = ft_parser(&stmnt, tokens, lim_token);
	clean_split(tokens, ft_spllen(tokens));
	if (!ret)
	{
		print_stmnt(stmnt, NULL);
		//exec_stmnt(stmnt);
	}
	if (stmnt)
		clean_all(&stmnt);
	return (ret);
}

int main(int argc, char *argv[], char *env[])
{
	get_env_hash(&g_data.env, env);
	write_key_value(&g_data.env, "a=*2 \"\"\"t\"*\"e\"*\"s\"*\"s\"* *3", 0);
	write_key_value(&g_data.env, "b=file", 0);
	if (argc == 2)
		return (exec_line(argv[1]));
}
