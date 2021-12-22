#include "parser.h"
#include "clean.h"

int count_args(char **tokens)
{
	int		count;

	count = 0;
	while (*tokens)
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

t_cmd	*ft_init_cmd(char **tokens)
{
	int		count;
	t_cmd	*cmd;

	cmd = ft_cmd_new();
	if (!cmd)
		return (NULL);
	cmd->redir = ft_redir_new();
	if (!cmd->redir)
	{
		clean_cmd(cmd);
		return (NULL);
	}
	count = count_args(tokens);
	if (count)
	{
		cmd->args = (char **) malloc(sizeof(char *) * (count + 1));
		if (!cmd->args)
		{
			clean_cmd(cmd);
			return (NULL);
		}
		cmd->args[count] = NULL;
	}
	return (cmd);
}

int ft_write_cmd(t_cmd *cmd, char ***tokens)
{
	int		ret;
	char	**cur;
	t_redir	*red;

	ret = 0;
	cur = cmd->args;
	red = cmd->redir;
	while (!ret && **tokens)
	{
		if (accept(lg, tokens))
			ret = ft_redir(red, tokens);
		else if (accept(wrd, tokens))
		{
			ret = ft_word(cur, tokens);
			cur++;
		}
		else
			break ;
	}
	if (ret)
		return (ret);
	return (0);
}

int ft_cmd(t_stmnt **stmnt, char **tokens)
{
	t_cmd	*cmd;
	int		ret;

	if (accept(lb, &tokens))
	{
		(*stmnt)->type = op_sbsh;
		return (ft_subshell((t_stmnt **)&(*stmnt)->oper1, tokens));
	}
	(*stmnt)->type = op_smpl;
	cmd = ft_init_cmd(tokens);
	if (!cmd)
		return (malloc_err);
	(*stmnt)->oper1 = cmd;
	ret = ft_write_cmd((*stmnt)->oper1, &tokens);
	if (ret)
		return (ret);
	else if (accept(lb, &tokens) || accept(rb, &tokens))
		return (syntax_error(syntax_err));
	return (0);
}

t_stmnt	*ft_oper(char ***oper, char **tokens, char **lim_token, t_token top)
{
	char	**cur_token;

	cur_token = lim_token;
	while (cur_token >= tokens && \
		type(*tokens) != top)
		cur_token--;
	if (cur_token < tokens)
		*oper = NULL;
	else
		*oper = cur_token;
	return (ft_stmnt_new());
}

int ft_stmnt(t_stmnt **stmnt, char **tokens, char **lim_token)
{
	char	**tpip;

	*stmnt = ft_oper(&tpip, tokens, lim_token, pp);
	if (!*stmnt)
		return (malloc_err);
	(*stmnt)->type = op_none;
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
		(*stmnt)->type = (ft_isoperator(*oper, (int)ft_strlen(*oper))\
						== ct_and + op_or);
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
