#include "parser.h"

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

int ft_subshell(t_stmnt **stmnt, t_redir *red, char ***tokens)
{
	*stmnt = ft_stmnt_new();
	ft_parser(stmnt, tokens);
	expect(rb, tokens);
	while (accept(lg, tokens))
		ft_redir(red, tokens);
	(*stmnt)->redir = red;


}

void ft_cmd(t_cmd **cmd, t_redir **red, char ***tokens)
{
	int		count;

	*cmd = NULL;
	*red = NULL;
	count = count_args(*tokens);
	*red = ft_redir_new();
	if (count)
	{
		(*cmd) = ft_cmd_new();
		(*cmd)->args = (char **) malloc(sizeof(char *) * count);
	}
	while (1)
	{
		if (accept(lg, tokens))
			ft_redir(*red, tokens);
		else if (count && accept(wrd, tokens))
			ft_word((*cmd)->args, tokens);
		else
			break ;
	}
}

void add_oper(t_stmnt **stmnt, t_cmd *cmd, char ***tokens)
{
	t_stmnt *new_stmnt;
	char 	*otoken;
	t_tstmnt stype;
	t_topers otype;

	otoken = (*tokens)[0];
	if (accept(lb, tokens))
	{
		stype = op_sbsh;
	}
	else if (accept(op, tokens))
	{
		new_stmnt = ft_stmnt_new();
		otype = ft_isoperator(otoken, ft_strlen(otoken));
		new_stmnt->type = op_or;
		if (otype = and)
			new_stmnt->type = op_and;
		new_stmnt->type1 = (*stmnt)->type;
		new_stmnt->oper1 = (*stmnt);
		*stmnt = new_stmnt;
	}
	else if (accept(pp, tokens))
	{
		cmd->next_cmd = ft_cmd_new();

	}
}

int ft_parser(t_stmnt **stmnt, char **tokens)
{
	t_cmd	*cmd;
	t_redir	*red;

	ft_cmd(&cmd, &red, &tokens);
	add_oper(stmnt, NULL, NULL);
	while (cmd || red)
	{
		ft_cmd(&cmd, &red, &tokens);
		add_oper(stmnt, NULL, NULL);
	}
}
