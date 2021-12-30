#include "parser.h"
#include "clean.h"

static int count_args(char **tokens)
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

static int write_word(char ***cur, char **tokens)
{
	char *tmp;

	tmp =  ft_strdup(tokens[-1]);
	if (!tmp)
		return (malloc_err);
	**cur = tmp;
	*cur += 1;
	return (0);
}


static t_cmd	*ft_init_cmd(char **tokens)
{
	int		count;
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redir = NULL;
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

static int ft_write_cmd(t_cmd *cmd, char ***tokens)
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
			ret = ft_redir(&red, tokens);
		else if (accept(wrd, tokens))
			ret = write_word(&cur, *tokens);
		else
			break ;
	}
	return (ret);
}

int ft_cmd(t_stmnt **stmnt, char **tokens, char **lim_token)
{
	t_cmd	*cmd;
	int		ret;

	if (accept(lb, &tokens))
	{
		(*stmnt)->type = op_sbsh;
		return (ft_subshell((t_stmnt **) &(*stmnt)->oper1, \
				&(*stmnt)->redir, tokens));
	}
	(*stmnt)->type = op_smpl;
	cmd = ft_init_cmd(tokens);
	if (!cmd)
		return (malloc_err);
	(*stmnt)->oper1 = cmd;
	ret = ft_write_cmd((*stmnt)->oper1, &tokens);
	if (ret)
		return (ret);
	else if (lim_token != tokens - 1)
		return (syntax_error(syntax_err, *tokens));
	return (0);
}
