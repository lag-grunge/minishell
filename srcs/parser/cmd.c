#include "../../includes/parser.h"
#include "../../includes/clean.h"

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

static int write_word(char **cur, char **tokens)
{
	char *tmp;

	tmp =  ft_strdup(tokens[-1]);
	if (!tmp)
		return (malloc_err);
	*cur = tmp;
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

static int ft_write_cmd(char **cmd_args, t_redir **cmd_red, \
						char **tokens, char **lim_token)
{
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	while (!ret && *tokens)
	{
		if (accept(lg, &tokens))
			ret = ft_redir(cmd_red, &tokens);
		else if (cmd_args && accept(wrd, &tokens))
		{
			ret = write_word(cmd_args + i, tokens);
			i++;
		}
		else if (accept(wrd, &tokens))
			continue ;
		else
			break ;
	}
	if (ret)
		return (ret);
	else if (tokens <= lim_token)
		return (syntax_error(syntax_err, *tokens, "cmd"));
	return (0);
}

int ft_cmd(t_stmnt **stmnt, char **tokens, char **lim_token)
{
	t_cmd	*cmd;

	if (accept(lb, &tokens))
	{
		if (stmnt)
		{
			(*stmnt)->type = op_sbsh;
			return (ft_subshell((t_stmnt **) &(*stmnt)->oper1, \
                &(*stmnt)->redir, tokens));
		}
		return (ft_subshell(NULL, NULL, tokens));
	}
	if (!stmnt)
		return (ft_write_cmd(NULL, NULL, tokens, lim_token));
	(*stmnt)->type = op_smpl;
	cmd = ft_init_cmd(tokens);
	if (!cmd)
		return (malloc_err);
	(*stmnt)->oper1 = cmd;
	return (ft_write_cmd(cmd->args, &cmd->redir, tokens, lim_token));
}
