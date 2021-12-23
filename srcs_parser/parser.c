#include "parser.h"
#include "clean.h"

static t_stmnt *ft_stmnt_new(void)
{
	t_stmnt *stmnt;

	stmnt = malloc(sizeof(t_stmnt) * 1);
	stmnt->type = 0;
	stmnt->oper1 = NULL;
	stmnt->oper2 = NULL;
	stmnt->redir = NULL;
	stmnt->next_stmnt = NULL;
	return (stmnt);
}

static t_stmnt	*ft_oper(char ***oper, char **tokens, char **lim_token, t_token top)
{
	char	**cur_token;

	cur_token = lim_token;
	while (cur_token >= tokens && \
		type(*cur_token) != top)
		cur_token--;
	if (cur_token < tokens)
		*oper = NULL;
	else
		*oper = cur_token;
	return (ft_stmnt_new());
}

static int ft_stmnt(t_stmnt **stmnt, char **tokens, char **lim_token)
{
	char	**tpip;

	*stmnt = ft_oper(&tpip, tokens, lim_token, pp);
	if (!*stmnt)
		return (malloc_err);
	if (tpip && (tpip - 1 >= tokens) && (tpip + 1 <= lim_token))
	{
		return (ft_cmd(stmnt, tokens) || \
			ft_stmnt(&(*stmnt)->next_stmnt, tpip + 1, lim_token));
	}
	else if (tpip)
		return (syntax_error(syntax_err));
	else
	{
		(*stmnt)->next_stmnt = NULL;
		return (ft_cmd(stmnt, tokens));
	}
}

int ft_parser(t_stmnt **stmnt, char **tokens, char **lim_token)
{
	char	**oper;

	*stmnt = ft_oper(&oper, tokens, lim_token, op);
	if (!*stmnt)
		return (malloc_err);
	if (oper && (oper - 1 >= tokens) && (oper + 1 <= lim_token))
	{
		(*stmnt)->type = ((ft_isoperator(*oper)\
 == ct_and) + op_or);
		return (ft_stmnt\
				((t_stmnt **)&(*stmnt)->oper1, tokens, oper - 1) || \
                ft_parser\
				((t_stmnt **)&(*stmnt)->oper2, oper + 1, lim_token));
	}
	else if (oper)
		return (syntax_error(syntax_err));
	else
		return (ft_stmnt\
			(stmnt, tokens, lim_token));
}
