#include "expansions.h"
#include "syntax.h"

static int	get_size(char *token)
{
	int	size;
	int	qlen;

	size = 0;
	while (*token)
	{
		if (*token == '\'' || *token == '\"')
		{
			qlen = quoting(token);
			if (qlen > 2)
				size += qlen - 2;
			if (qlen >= 2)
				token += qlen;
			if (qlen >= 2)
				continue ;
		}
		token++;
		size++;
	}
	return (size);
}

static char	*quote_copy(char *new_token, char *token, int *i_ptr)
{
	int	qlen;

	qlen = quoting(token);
	if (qlen == 2)
		return (token + 2);
	ft_strlcat(new_token, token + 1, *i_ptr + qlen - 2 + 1);
	*i_ptr += qlen - 2;
	return (token + qlen);
}

char	*quote_removal(char *token)
{
	int		new_len;
	int		i;
	char	*new_token;

	new_len = get_size(token);
	new_token = ft_calloc(new_len + 1, sizeof(char));
	i = 0;
	while (*token)
	{
		if ((*token != '\'' && *token != '\"') || quoting(token) == 1)
		{
			new_token[i] = *token;
			token++;
			i++;
		}
		else
			token = quote_copy(new_token, token, &i);
	}
	return (new_token);
}

int	quoting(char *read_line)
{
	char	quote;
	char	*res;

	quote = *read_line;
	res = ft_strchr(read_line + 1, quote);
	if (!res)
		return (1);
	return (res - read_line + 1);
}
