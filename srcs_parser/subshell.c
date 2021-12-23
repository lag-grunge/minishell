#include "syntax.h"
#include "parser.h"

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
		else
			tokens = nextsym(tokens);
	}
	return (tokens - 2);
}

static int	empty_brackets(char **lim_token)
{
	return (type(*lim_token) == lb);
}

int ft_subshell(t_stmnt **stmnt, char **tokens)
{
	char	**lim_token;
	int		ret;

	if (!check_brackets(tokens))
		return syntax_error(syntax_err);
	lim_token = close_bracket(tokens);
	if (empty_brackets(lim_token))
		return syntax_error(syntax_err);
	ret = ft_parser(stmnt, tokens, lim_token);
	if (ret)
		return (ret);
	tokens = lim_token + 1;
	while (!ret && accept(lg, &tokens))
		ret = ft_redir((*stmnt)->redir, &tokens);
	if (accept(wrd, &tokens))
		return (syntax_error(syntax_err));
	return (0);
}
