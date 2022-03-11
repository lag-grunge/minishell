#include "../../includes/syntax.h"
#include "../../includes/parser.h"

int check_brackets(char **tokens, char **lim_token)
{
	int	brackets;

	brackets = 0;
	while (tokens <= lim_token)
	{
		if (accept(lb, &tokens))
			brackets++;
		else if (accept(rb, &tokens))
			brackets--;
		else
			tokens++;
        if (brackets < 0)
            return (syntax_error(syntax_err, ")", "bash: syntax:"));
	}
	if (!brackets)
		return (0);
    return (syntax_error(syntax_err, "newline'", "bash: syntax: ("));
}

static int condition(char **tokens, char **lim_token, int direction)
{
	if (direction == 1 && lim_token && tokens <= lim_token)
		return (1);
	else if (direction == 1 && !lim_token && *tokens)
		return (1);
    else if (direction == -1 && lim_token && tokens >= lim_token)
        return (1);
//    else if (direction == -1 && !lim_token && *tokens)
//        return (1);
	return (0);
}

char **close_bracket(char **tokens, char **lim_token, int direction)
{
	int	brackets;

    brackets = direction;
    while (condition(tokens, lim_token, direction))
	{
        if ((*tokens)[0] == '(')
            brackets++;
        else if ((*tokens)[0] == ')')
            brackets--;
        if (!brackets)
            return (tokens);
		tokens += direction;
	}
    return (NULL);
}


static int	empty_brackets(char **lim_token)
{
	return (type(*lim_token) == lb);
}

int ft_parenthesis(t_stmnt **stmnt, t_redir **red, char **tokens)
{
	char	**lim_token;
	int		ret;

	lim_token = close_bracket(tokens, NULL, 1) - 1;
	if (!stmnt && empty_brackets(lim_token))
		return syntax_error(syntax_err, lim_token[1], "ft_parenthesis");
	if (!stmnt)
		ret = ft_preparser(tokens, lim_token);
	else
		ret = ft_parser(stmnt, tokens, lim_token);
	if (ret)
		return (ret);
	tokens = lim_token + 2;
	while (*tokens && !ret && accept(lg, &tokens))
		ret = ft_redir(red, &tokens);
	if (!stmnt && *tokens && type(*tokens) == wrd)
		return (syntax_error(syntax_err, tokens[-1], "ft_parenthesis"));
	return (ret);
}
