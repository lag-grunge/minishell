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

int *ft_write_cmd(t_stmnt **stmnt, t_cmd *cmd, char ***tokens)
{
	int		ret;

	ret = 0;
	while (!ret)
	{
		if (accept(lg, &tokens))
			ret = ft_redir(cmd->redir, &tokens);
		else if (accept(wrd, &tokens))
			ret = ft_word(cmd->args, &tokens);
		else
			break ;
	}
	if (ret)
		return (ret);
	(*stmnt)->oper1 = cmd;
	return (0);
}

int ft_cmd(t_stmnt **stmnt, int *t, char **tokens)
{
	t_cmd	*cmd;

	if (accept(ct_lbr, tokens))
	{
		*t = op_sbsh;
		return (ft_subshell(stmnt, tokens));
	}
	*t = op_smpl;
	cmd = ft_init_cmd(tokens);
	if (!cmd)
		return (malloc_err);
	ft_write_cmd(stmnt, cmd, &tokens);
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

int ft_stmnt(t_stmnt **stmnt, int *t, char **tokens, char **lim_token)
{
	char	**tpip;
	int 	ret;

	*stmnt = ft_oper(&tpip, tokens, lim_token, pp);
	if (!*stmnt)
		return (malloc_err);
	if (tpip && (tpip - 1 >= tokens) && (tpip + 1 <= lim_token))
	{
		ret = ft_cmd(stmnt, t, tokens);
		ft_stmnt(&(*stmnt)->next_stmnt, NULL, tpip + 1, lim_token);
	}
	else if (tpip)
		return (syntax_error(syntax_err));
	else
	{
		(*stmnt)->next_stmnt = NULL;
		return (ft_cmd(stmnt, NULL, tokens));
	}
}

int ft_parser(t_stmnt **stmnt, int *t, char **tokens, char **lim_token)
{
	char	**oper;

	*stmnt = ft_oper(&oper, tokens, lim_token, op);
	if (!*stmnt)
		return (malloc_err);
	if (oper && (oper - 1 >= tokens) && (oper + 1 <= lim_token))
	{
		if (ft_isoperator(*oper, ft_strlen(*oper) == ct_and))
			*t = op_and;
		else
			*t = op_or;
		(*stmnt)->type = *t;
		return (ft_stmnt\
				(&(*stmnt)->oper1, &(*stmnt)->type1, tokens, oper - 1) || \
				ft_parser\
				(&(*stmnt)->oper2, &(*stmnt)->type2, oper + 1, lim_token));
	}
	else if (oper)
		return (syntax_error(syntax_err));
	else
	{
		(*stmnt)->type = op_none;
		return (ft_stmnt\
			(&(*stmnt)->oper1, &(*stmnt)->type1, tokens, oper - 1));
	}
}
