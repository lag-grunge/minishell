#include "../includes/minishell.h"
#include "syntax.h"
#include "expansions.h"

static int	test_pattern(char **next, char **token)
{
	char	lim;

	lim = '*';
	if ((**token == '\"' || **token == '\'') && quoting(*token) > 1)
	{
		lim = **token;
		(*token)++;
	}
	while (**token != lim)
	{
		if (lim == '*' && ((**token == '\"' || **token == '\'') && \
			quoting(*token) > 1) && !test_pattern(next, token))
			return (0);
		if (**token != **next)
			return (0);
		else if (!**token)
			return (1);
		(*token)++;
		(*next)++;
	}
	if (lim != '*')
		(*token)++;
	if (lim != '*' && !**token && **next)
		return (0);
	return (1);
}

static int	match_next(char *d_name, char *token, int quote)
{
	int	ret;

	ret = 0;
	if (quote)
	{
		while ((*token == '\'' || *token == '\"') && token[1] == *token)
			token += 2;
		if ((*token != '\'' && *token != '\"') || quoting(token) == 1)
			return (match_next(d_name, token, 0));
	}
	d_name = ft_strchr(d_name, token[quote]);
	while (d_name && *d_name && !ret)
	{
		ret = match(d_name, token);
		d_name = ft_strchr(d_name + 1, token[quote]);
	}
	return (ret);
}

int	match(char *d_name, char *token)
{
	static int	ret;

	while (*token != '*')
	{
		ret = test_pattern(&d_name, &token);
		if (!ret)
			return (0);
		else if (!*token && *token == *d_name)
			return (1);
	}
	while (*token == '*')
		token++;
	if (!*token)
		return (1);
	if ((*token != '\'' && *token != '\"') || quoting(token) == 1)
		return (match_next(d_name, token, 0));
	return (match_next(d_name, token, 1));
}
