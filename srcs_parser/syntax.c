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
	return (0);
}

t_redir	*add_redir_item(t_redir **red)
{
	t_redir	*r;

	r = *red;
	if (!r->word)
		return (r);
	while (r->next)
		r = r->next;
	r->next = ft_redir_new();
	return (r->next);
}

static int write_redir(t_redir *redirect, char **tokens)
{
	char		*red_token;
	char 		*wrd_token;
	t_ctrls		red_type;
	t_redir		*red;

	red = add_redir_item(&redirect);
	if (!red)
		return (malloc_err);
	red_token = tokens[-2];
	wrd_token = tokens[-1];
	red_type = ft_isoperator(red_token, (int)ft_strlen(red_token));
	if (red_type == ct_ltlt)
		red->type = red_rh_doc;
	else if (red_type == ct_lt)
		red->type = red_rifile;
	else if (red_type == ct_gt)
		red->type = red_wofile;
	else if (red_type == ct_gtgt)
		red->type = red_aofile;
	red->word = ft_strdup(wrd_token);
	if (!red->word)
		return (malloc_err);
	return (0);
}

int ft_redir(t_redir *red, char ***tokens)
{
	if (!expect(wrd, tokens))
		return (syntax_error(syntax_err));
	if (red)
		return (write_redir(red, *tokens));
	return (0);
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
		return syntax_error(syntax_err);
	lim_token = close_bracket(tokens);
	ret = ft_parser(stmnt, tokens, lim_token - 1);
	if (ret)
		return (ret);
	tokens = lim_token + 1;
	while (!ret && accept(lg, &tokens))
		ret = ft_redir(&(*stmnt)->redir, &tokens);
	if (accept(wrd, &tokens))
		return (syntax_error(syntax_err));
	return (0);
}

