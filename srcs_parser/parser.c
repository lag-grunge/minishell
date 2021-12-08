#include "minishell.h"

typedef enum {rdr, wrd, op, pp, lb, rb} token;

token	type(char *cur)
{
	int ret;

	ret = ft_isoperator(cur);
	if (ret >= ltlt && ret <= gt)
		return (rdr);
	else if (ret == or || ret == and)
		return (op);
	else if (ret == pip)
		return (pp);
	else if (ret == lbr)
		return (lb);
	else if (ret == rbr)
		return (rb);
	else
		return (wrd);
}

int expect(token t, char ***cur)
{
	if (accept(t, cur))
		return (1);
	printf("unexpected token\n");
	return (0);
}

char **nextsym(char **cur)
{
	return (cur + 1);
}

int accept(token t, char ***cur)
{
	if (t == type(**cur))
	{
		*cur = nextsym(*cur);
		return (1);
	}
	return (0);
}

int word(char ***tokens)
{
	if (accept(lb, tokens))
	{
		printf("unexpected token\n");
		return (0);
	}
	*tokens = nextsym(*tokens);
	return (1);
}

int	ft_redir(char ***tokens)
{
	return (expect(wrd, tokens));
}

int	ft_subshell(char ***tokens)
{
	int ret;

	ft_parser(*tokens + 1, 1);

}

int oper(char **tokens)
{

	return (1);
}

int ft_parser(char *tokens[], int sub)
{
	int ret;
	t_cmd	*cmd;
	t_opers *opers;

	opers = ft_oper_new();
	cmd = ft_cmd_new();
	opers->oper1 = cmd;
	ret = 1;
	while (*tokens && )
	{
		if (accept(rdr, &tokens))
			ret = ft_redir(&tokens);
		else if (accept(wrd, &tokens))
			ret = ft_word(&tokens);
		else if (accept(lb, &tokens))
			ret = ft_subshell(&tokens);
	}
}
