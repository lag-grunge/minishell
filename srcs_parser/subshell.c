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

char **close_bracket(char **tokens)
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
	return (tokens - 1);
}

static int	empty_brackets(char **lim_token)
{
	return (type(*lim_token) == lb);
}

int ft_subshell(t_stmnt **stmnt, t_redir **common_red, char **tokens)
{
	char	**lim_token;
	int		ret;

	if (!check_brackets(tokens))
		return syntax_error(syntax_err, "newline");
	lim_token = close_bracket(tokens) - 1;
	if (empty_brackets(lim_token))
		return syntax_error(syntax_err, lim_token[1]);
	ret = ft_parser(stmnt, tokens, lim_token);
	if (ret)
		return (ret);
	tokens = lim_token + 2;
	while (!ret && accept(lg, &tokens))
		ret = ft_redir(common_red, &tokens);
	if (accept(wrd, &tokens))
		return (syntax_error(syntax_err, tokens[-1]));
	return (0);
}
