#include "../../includes/parser.h"
#include "../../includes/clean.h"
#include "expansions.h"
#include "environment.h"

static int count_args(char **tokens, char *pwd, char **lim_token)
{
	int	count;
	char **spl_token;

	count = 0;
	while (*tokens)
	{
		if (accept(lg, &tokens))
			ft_redir(NULL, &tokens);
		else if (accept(wrd, &tokens))
		{
			spl_token = variable_expansion(tokens - 1, g_data.env);
			count += count_filename_expansion(pwd, spl_token);
			clean_split(spl_token, ft_spllen(spl_token));
		}
		else
			break ;
	}
	if (tokens <= lim_token)
		return (-syntax_error(syntax_err, *tokens, "cmd"));
	return (count);
}

int		write_word(char **cur, char *tokens)
{
	char *tmp;

	tmp =  ft_strdup(tokens);
	if (!tmp)
		exit (malloc_err);
	*cur = tmp;
	return (0);
}


static int ft_init_cmd(t_cmd **cmd, char **tokens, char *pwd, char **lim_token)
{
	int		count;

	*cmd = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	if (!*cmd)
		exit (malloc_err);
	(*cmd)->args = NULL;
	(*cmd)->redir = NULL;
	count = count_args(tokens, pwd, lim_token);
	if (count == -syntax_err)
		return (syntax_err);
	if (count)
	{
		(*cmd)->args = (char **) malloc(sizeof(char *) * (count + 1));
		if (!(*cmd)->args)
			exit (malloc_err);
		(*cmd)->args[count] = NULL;
	}
	return (0);
}

static int ft_write_cmd(char **cmd_args, t_redir **cmd_red, char **tokens, char *pwd)
{
	int		ret;
	int 	i;
	char 	**spl_token;

	ret = 0;
	i = 0;
	while (!ret && *tokens)
	{
		if (accept(lg, &tokens))
			ret = ft_redir(cmd_red, &tokens);
		else if (cmd_args && accept(wrd, &tokens))
		{
			spl_token = variable_expansion(tokens - 1, g_data.env);
			i += filename_expansion(cmd_args + i, pwd, spl_token);
			clean_split(spl_token, ft_spllen(spl_token));
		}
		else if (accept(wrd, &tokens))
			continue ;
		else
			break ;
	}
	return (ret);
}

int ft_cmd(t_stmnt **stmnt, char **tokens, char **lim_token)
{
	char	*pwd;
	t_cmd	**cmd;
	int		ret;

	if (accept(lb, &tokens))
	{
		if (stmnt)
		{
			(*stmnt)->type = op_sbsh;
			return (ft_parenthesis((t_stmnt **) &(*stmnt)->oper1, \
                &(*stmnt)->redir, tokens));
		}
		return (ft_parenthesis(NULL, NULL, tokens));
	}
	if (!stmnt)
		return (ft_write_cmd(NULL, NULL, tokens, NULL));
	(*stmnt)->type = op_smpl;
	pwd = get_value(g_data.env, "PWD");
	cmd = (t_cmd **)&(*stmnt)->oper1;
	ret = ft_init_cmd(cmd, tokens, pwd, lim_token);
	if (!ret)
		ret = ft_write_cmd((*cmd)->args, &(*cmd)->redir, tokens, pwd);
	free(pwd);
	return  (ret);
}