#include "../../includes/syntax.h"
#include "../../includes/parser.h"

int check_brackets(char **tokens)
{
	int	brackets;

	brackets = 1;
	while (*tokens && brackets)
	{
		if (accept(lb, &tokens))
			brackets++;
		else if (accept(rb, &tokens))
			brackets--;
		else
			tokens++;
	}
	if (!brackets)
		return (1);
	return (0);
}

static int condition(char **tokens, char **lim_token, int br)
{
	if (lim_token && tokens <= lim_token && br)
		return (1);
	else if (!lim_token && *tokens && br)
		return (1);
	return (0);
}

char **close_bracket(char **tokens, char **lim_token)
{
	int	brackets;

	brackets = 1;
	while (condition(tokens,lim_token, brackets))
	{
		if (accept(lb, &tokens))
			brackets++;
		else if (accept(rb, &tokens))
			brackets--;
		else
			tokens++;
	}
	if (brackets)
		return (NULL);
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

	if (!stmnt && !check_brackets(tokens))
		return syntax_error(syntax_err, "newline", "ft_subshell");
	lim_token = close_bracket(tokens, NULL) - 1;
	if (!stmnt && empty_brackets(lim_token))
		return syntax_error(syntax_err, lim_token[1], "ft_subshell");
	if (!stmnt)
		ret = ft_preparser(tokens, lim_token);
	else
		ret = ft_parser(stmnt, tokens, lim_token);
	if (ret)
		return (ret);
	tokens = lim_token + 2;
	while (*tokens && !ret && accept(lg, &tokens))
		ret = ft_redir(common_red, &tokens);
	if (!stmnt && *tokens && type(*tokens) == wrd)
		return (syntax_error(syntax_err, tokens[-1], "ft_subshell"));
	return (ret);
}
