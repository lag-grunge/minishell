#include "parser.h"


int ft_cmd(t_cmd *cmd, char ***tokens)
{
	if (accept(lg, tokens))
		ft_redir(cmd, tokens);
	else if (accept(wrd, tokens))
		ft_bin(cmd, tokens);

}

int ft_subshell(t_cmd *cmd, char ***tokens, int subshell)
{

}

int ft_parser(t_opers **opers, char *read_line)
{
	int ret;
	t_cmd	*cmd;
	char **tokens;

	tokens = get_tokens(read_line);
	cmd = ft_cmd_new();
	ret = ft_cmd(cmd, &tokens);
	while (ret != op_none)
	{
		add_oper(opers, ret, &tokens);
		cmd = ft_cmd_new();
		ret = ft_cmd(cmd, &tokens);
	}

}
