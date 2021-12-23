#include "minishell.h"
#include "syntax.h"


static char	*oper_token(char *read_line, int *len)
{
	while (ft_isspace(*read_line))
		read_line++;
	if (ft_ismeta(*read_line))
		return (meta(read_line, len));
	return (word(read_line, len));
}

static size_t get_number(char *read_line)
{
	int	num;

	num = 0;
	while (read_line && *read_line)
	{
		read_line = oper_token(read_line, NULL);
		num++;
	}
	return (num);
}

char **get_tokens(char *read_line, int *empty)
{
	size_t	num;
	char 	**tokens;
	int		i;
	int		len;

	num = get_number(read_line);
	if (!num)
	{
		*empty = 1;
		return (NULL);
	}
	tokens = malloc(sizeof(char *) * (num + 1));
	if (!tokens)
		return (NULL);
	tokens[num] = NULL;
	i = 0;
	while (*read_line)
	{
		read_line = oper_token(read_line, &len);
		tokens[i] = ft_substr(read_line - len, 0, len);
		i++;
	}
	return (tokens);
}
