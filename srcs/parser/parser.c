#include "../../includes/parser.h"
#include "../../includes/clean.h"

static t_stmnt *ft_stmnt_new(void)
{
	t_stmnt *stmnt;

	stmnt = malloc(sizeof(t_stmnt) * 1);
	stmnt->type = 0;
	stmnt->oper1 = NULL;
	stmnt->oper2 = NULL;
	stmnt->redir = NULL;
	stmnt->pid = 0;
	stmnt->next_stmnt = NULL;
	return (stmnt);
}

static int ft_oper(char ***oper, char **tokens, char **lim_token, t_token top)
{
	char	**cur_token;

	cur_token = tokens;
	while (cur_token && cur_token <= lim_token && \
		type(*cur_token) != top)
		{
		if (accept(lb, &cur_token))
			cur_token = close_bracket(cur_token, lim_token);
        cur_token++;
	}
	if (cur_token && (cur_token == lim_token || cur_token == tokens))
		return (syntax_error(syntax_err, *cur_token, "minishell"));
	else if (!cur_token || cur_token > lim_token)
		*oper = NULL;
	else
		*oper = cur_token;
	return (0);
}

static int ft_stmnt(t_stmnt **stmnt, char **tokens, char **lim_token)
{
	char	**tpip;
	int		ret;

	ret = ft_oper(&tpip, tokens, lim_token, pp);
	if (ret)
		return (ret);
	if (stmnt)
	{
		*stmnt = ft_stmnt_new();
		if (!*stmnt)
			return (malloc_err);
	}
	if (!tpip)
		return (ft_cmd(stmnt, tokens, lim_token));
	if (stmnt)
	{
		ret = ft_cmd(stmnt, tokens, tpip - 1);
        if (ret)
            return (ret);
        return (ft_stmnt(&(*stmnt)->next_stmnt, tpip + 1, lim_token));
	}
    ret = ft_cmd(NULL, tokens, tpip - 1);
    if (ret)
        return (ret);
    return (ft_stmnt(NULL, tpip + 1, lim_token));
}

int ft_parser(t_stmnt **stmnt, char **tokens, char **lim_token)
{
	char	**oper;
	int		ret;

	ret = ft_oper(&oper, tokens, lim_token, op);
	if (ret)
		return (ret);
	if (oper)
	{
		*stmnt = ft_stmnt_new();
		if (!*stmnt)
			return (malloc_err);
		(*stmnt)->type = ((ft_isoperator(*oper)\
 == ct_and) + op_or);
		return (ft_stmnt\
				((t_stmnt **)&(*stmnt)->oper1, tokens, oper - 1) || \
                ft_parser\
				((t_stmnt **)&(*stmnt)->oper2, oper + 1, lim_token));
	}
	return (ft_stmnt\
			(stmnt, tokens, lim_token));
}

int ft_preparser(char **tokens, char **lim_token)
{
	char	**oper;
	int		ret;

    	if (check_brackets(tokens, lim_token))
        	return (syntax_err);
	ret = ft_oper(&oper, tokens, lim_token, op);
	if (ret)
		return (ret);
	if (oper)
	{
		return (ft_stmnt\
				(NULL, tokens, oper - 1) || \
                ft_preparser\
				(oper + 1, lim_token));
	}
	return (ft_stmnt\
			(NULL, tokens, lim_token));
}
