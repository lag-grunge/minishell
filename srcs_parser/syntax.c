#include "syntax.h"

int ft_bin(t_cmd *cmd, char ***tokens)
{
	if (accept(lg, tokens))
		return (ft_redir(NULL, tokens);
	else if (accept(wrd, tokens))
		return (ft_args(tokens);
	else if (accept(op, tokens))
		return (ft_oper(tokens);
	else if (accept(pp, tokens))
		return (ft_pipe(tokens);
	else if (accept(lb, tokens))
		return (error());
	else if (accept(rb, tokens))
	{
//		if (subshell)
//			return (-1);
		return (error());
	}
}

int ft_args(char ***tokens)
{
	if (accept(lg, tokens))
		return (ft_redir(NULL, tokens);
	else if (accept(wrd, tokens))
		return (ft_args(tokens);
	else if (accept(op, tokens))
		return (ft_oper(tokens));
	else if (accept(pp, tokens))
		return (ft_pipe(tokens);
	else if (accept(lb, tokens))
		return (error());
	else if (accept(rb, tokens))
	{
		return (error());
	}
}

int ft_redir(t_cmd *cmd, char ***tokens)
{
	if (!expect(wrd, tokens))
		return (0);
	if (cmd)
		write_redir(cmd, *tokens);

}

int	ft_subshell(char ***tokens, int subshell)
{
	int ret;

}

int ft_oper(char ***tokens)
{

	return (1);
}

int ft_pipe(char ***tokens)
{

}

