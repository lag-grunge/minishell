#include "parser.h"
#include "clean.h"

int count_args(char **tokens)
{
	int	count;

	count = 0;
	while (1)
	{
		if (accept(lg, &tokens))
			ft_redir(NULL, &tokens);
		else if (accept(wrd, &tokens))
			count++;
		else
			break ;
	}
	return (count);
}

static t_token	cmd_end(char ***tokens) {
	if (accept(op, tokens))
		return (op);
	else if (accept(pp, tokens))
		return (pp);
	else if (accept(lb, tokens))
		return (lb);
	else if (accept(rb, tokens))
		return (rb);
}

void ft_cmd(t_stmnt **stmnt, char ***tokens)
{
	int		count;
	t_cmd	*cmd;
	t_stmnt *new_stmnt;

	cmd = ft_cmd_new();
	cmd->red = ft_redir_new();
	count = count_args(*tokens);
	if (count)
		cmd->args = (char **)malloc(sizeof(char *) * count);
	while (1)
	{
		if (accept(lg, tokens))
			ft_redir(cmd->redir, tokens);
		else if (count && accept(wrd, tokens))
			ft_word(cmd->args, tokens);
		else
			break ;
	}
	if (cmd->args || cmd->redir)
	{
		*stmnt = ft_stmnt_new();
		(*stmnt)->type = op_smpl;
		(*stmnt)->type1 = op_smpl;
		(*stmnt)->oper1 = cmd;
	}
	else
		clean_cmd(cmd);
}

void add_oper(t_stmnt **stmnt, char ***tokens)
{
	t_stmnt *new_stmnt;

	if (accept(pp, tokens))
	{
		(*stmnt)->next_stmnt = ft_stmnt_new();
	}
	else if (accept(op, tokens))
	{
		new_stmnt = ft_stmnt_new();
		new_stmnt->type = op_or;
		if (ft_isoperator((*tokens)[-1], ft_strlen((*tokens)[-1])) == and)
			new_stmnt->type = op_and;
		new_stmnt->type1 = (*stmnt)->type;
		new_stmnt->oper1 = (*stmnt);
		*stmnt = new_stmnt;
	}
}

static t_token parse_brackets(t_stmnt **stmnt, char ***tokens, char **lim_token)
{
	t_token	ret;

	ret = lb;
	if (accept(lb, tokens))
	{
		if ((*stmnt)->type == op_smpl && \
			(((t_cmd *)(*stmnt)->oper1)->args || \
			((t_cmd *)(*stmnt)->oper1)->redir))
			error();
		ft_subshell(&new_stmnt, tokens);
		if ((*stmnt)->type == op_and || (*stmnt)->type == op_or)
		{
			(*stmnt)->type2 = op_sbsh;
			(*stmnt)->oper2 = new_stmnt;
		}
		else
		{
			*stmnt = new_stmnt;
		}
	}
	else if (lim_token && lim_token == *tokens)
		ret = rb;
	else if (accept(rb, tokens))
		error();
	return (ret);
}

int ft_parser(t_stmnt **stmnt, char **tokens, char **lim_token)
{
	int 	ret;

	while (*tokens)
	{
		ft_cmd(stmnt, &tokens);
		if (parse_brackets(stmnt, &tokens, lim_token) == rb)
			break ;
		add_oper(stmnt, &tokens);
	}
	return (1);
}
