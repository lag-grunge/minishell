#include "minishell.h"

int ft_parser(char *tokens[]) {
	int ret;
	t_cmd	*cmd;
	t_opers *opers;

	opers = ft_oper_new();
	cmd = ft_cmd_new();
	opers->oper1 = cmd;
	while (*tokens)
	{
		ret = ft_isoperator(*tokens, ft_strlen(*tokens));
		if (ret == pip)
			ft_parser_pipe();
		else if (ret == or  || ret == and)
			ft_parser_opers();
		else if (ret == lbr)
			ft_parser_sbsh();
		else if (ret >= ltlt || ret <= gtgt)
			ft_parser_redir();
		else
			ft_parser_cmd_args();
	}

}