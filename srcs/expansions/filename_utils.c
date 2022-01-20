#include "../includes/minishell.h"

static int test_pattern(char **next, char **token)
{
	char	lim;

	lim = '*';
	if (**token == '\"' ||  **token == '\'')
		lim = **token;
	if (**token == '\"' ||  **token == '\'')
		(*token)++;
	while (**token != lim)
	{
		if (lim == '*' && (**token == '\"' ||  **token == '\'') \
			&& !test_pattern(next, token))
			return (0);
		if (**token != **next)
			return (0);
		else if (!**token)
			return (1);
		(*token)++;
		(*next)++;
	}
	if (**token == '\"' || **token== '\'')
		(*token)++;
	if (lim != '*' && !**token && **next)
		return (0);
	return (1);
}

int	match(char *d_name, char *token)
{
	static int	ret;

	if (*token != '*')
	{
		ret = test_pattern(&d_name, &token);
		if (!ret)
			return (0);
	}
	while ((*token == '\'' || *token == '\"') && *token == token[1])
		token += 2;
	while (*token == '*')
		token++;
	if (!*token)
		return (1);
	if (*token != '\'' && *token != '\"')
		d_name = ft_strchr(d_name, *token);
	else if (*token != token[1])
		d_name = ft_strchr(d_name, token[1]);
	if (!d_name)
		return (0);
	ret = 0;
	while (d_name && *d_name && !ret)
	{
		ret = match(d_name, token);
		d_name = ft_strchr(d_name + 1, *token);
	}
	return (ret);
}