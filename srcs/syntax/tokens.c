#include "../../includes/minishell.h"
#include "../../includes/syntax.h"

static int	trim_space(char **read_line)
{
	while (ft_isspace(**read_line))
		(*read_line) += 1;
	if (!**read_line)
		return (1);
	return (0);
}

static char	*oper_token(char *read_line, int *len)
{
	char *ret;
	char *tmp;

	if (ft_ismeta(*read_line))
	{
		tmp = NULL;
		ret = ft_meta(read_line, len, &tmp);
		if (tmp)
		{
			syntax_error(syntax_err, tmp, "tokens");
			free(tmp);
		}
		return (ret);
	}
	return (word(read_line, len));
}

static size_t get_number(char *read_line)
{
	int	num;

	num = 0;
	while (read_line && *read_line)
	{
		if (trim_space(&read_line))
			break ;
		read_line = oper_token(read_line, NULL);
		if (!read_line)
			return (0);
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
		if (trim_space(&read_line))
			break ;
		read_line = oper_token(read_line, &len);
		tokens[i] = ft_substr(read_line - len, 0, len);
		i++;
	}
	return (tokens);
}
