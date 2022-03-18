#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/environment.h"
#include "exec_stmnt.h"
#include "signal_dispose.h"
#include "biltins.h"

void	print_stmnt(t_stmnt *stmnt, char *pos);

int	exec_line(char *read_line)
{
	char		**tokens;
	char		**lim_token;
	t_stmnt		*stmnt;
	int			ret;

	stmnt = NULL;
	tokens = NULL;
	ret = 0;
	tokens = get_tokens(read_line, &ret);
	if (!tokens && ret == syntax_err)
		g_data.last_stat = 2;
	if (!tokens)
		return (0);
	lim_token = tokens + ft_spllen(tokens) - 1;
	ret = ft_preparser(tokens, lim_token);
	if (!ret)
		ret = ft_parser(&stmnt, tokens, lim_token);
	clean_split(tokens, ft_spllen(tokens));
	if (!ret)
		exec_stmnt(stmnt, &ret, 0);
	else if (ret == syntax_err)
		g_data.last_stat = 2;
	if (stmnt)
		clean_all(&stmnt);
	return (ret);
}

int	main(int argc, char *argv[], char *env[])
{
	char	*line;

	signal_dispose(main_shell);
	get_env_hash(&g_data.env, env);
	increment_shell_level();
	rl_outstream = stderr; // for tests
	if (argc > 2)
		return (1);
	else if (argc == 2)
		return (exec_line(argv[1]));
	while (1)
	{
		line = readline("minishell>");
		if (!line)
			ft_exit(NULL);
		add_history(line);
		exec_line(line);
		free(line);
	}
	return (0);
}
