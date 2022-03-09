#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/environment.h"
#include "exec_stmnt.h"
#include "signal_dispose.h"
#include "biltins.h"

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
	if (!tokens && !ret)
		return (malloc_err);
	else if (!tokens)
		return (0);
	lim_token = tokens + ft_spllen(tokens) - 1;
	ret = ft_preparser(tokens, lim_token);
	if (!ret)
		ret = ft_parser(&stmnt, tokens, lim_token);
	clean_split(tokens, ft_spllen(tokens));
	if (!ret  && try_openfiles(stmnt) == 0)
		exec_stmnt(stmnt, &ret,  0);
	else if (!ret)
	{
		set_value(&g_data.env, "last_status", ft_strdup("1"));
		ret = 1;
	}
	if (stmnt)
		clean_all(&stmnt);
	return (ret);
}

int main(int argc, char *argv[], char *env[])
{
	char 			*line;

	signal_dispose(main_shell);
	get_env_hash(&g_data.env, env);
	rl_outstream = stderr; // for tests
	if (argc > 2)
		return (1);
	else if (argc == 2)
		return (exec_line(argv[1]));
	while (1)
	{
		line = readline("minishell>");
		if (!line)
			ft_exit(NULL, &g_data);
		add_history(line);
		exec_line(line);
		free(line);
	}
	return (0);
}
