#include "syntax.h"
#include "parser.h"

static void write_args(char **args, char **tokens)
{
	char *args_token;

	args_token = tokens[-1];
	*args = ft_strdup(args_token);
}

int ft_word(char **args, char ***tokens)
{
	if (args)
		write_args(args, *tokens);
}


static void write_redir(t_redir *red, char **tokens)
{
	char		*red_token;
	char 		*wrd_token;
	t_ctrls		red_type;

	red_token = tokens[-2];
	wrd_token = tokens[-1];
	red_type = ft_isoperator(red_token, ft_strlen(red_token));
	if (red_type == ct_ltlt)
	{
		red->in = red_rh_doc;
		red->lim = ft_strdup(wrd_token);
	}
	else if (red_type == ct_lt)
	{
		red->in = red_rifile;
		red->infile = ft_strdup(wrd_token);
	}
	else if (red_type == ct_gt || red_type == ct_gtgt)
	{
		red->outfile = ft_strdup(wrd_token);
		red->out = red_wofile;
		if (red_type == ct_gtgt)
			red->out = red_aofile;
	}
}

int ft_redir(t_redir *red, char ***tokens)
{
	if (!expect(wrd, tokens))
	{
		syntax_error(0);
		return (syntax_err);
	}
	if (red)
		write_redir(red, *tokens);
}

static int  check_brackets(char **tokens)
{
	int	brackets;

	brackets = 1;
	while (*tokens && brackets >= 0)
	{
		if (accept(lb, &tokens))
			brackets++;
		else if (accept(rb, &tokens))
			brackets--;
		tokens = nextsym(tokens);
	}
	if (!*tokens && !brackets)
		return (1);
	return (0);
}

static char **close_bracket(char **tokens)
{
	int	brackets;

	brackets = 1;
	while (brackets)
	{
		if (accept(lb, &tokens))
			brackets++;
		else if (accept(rb, &tokens))
			brackets--;
		tokens = nextsym(tokens);
	}
	return (tokens);
}

int ft_subshell(t_stmnt **stmnt, char **tokens)
{
	char	**lim_token;
	int		ret;

	if (!check_brackets(tokens))
	{
		syntax_error(0);
		return (syntax_err);
	}
	lim_token = close_bracket(tokens);
	(*stmnt)->type = op_sbsh;
	ret = ft_parser(&(*stmnt)->oper1, tokens, lim_token - 1);
	tokens = lim_token + 1;
	while (ret && accept(lg, &tokens))
		ft_redir((*stmnt)->redir, &tokens));

	if (accept(wrd, &tokens))
	{
		syntax_error(0);
		return (syntax_err);
	}
	else if

}

