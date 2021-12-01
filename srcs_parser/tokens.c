#include "minishell.h"

int		ft_ismeta(int c)
{
	if (c == '<' || c == '>')
		return (1);
	else if (c == '|' || c == '&')
		return (1);
	else if (c == '(' || c == ')')
		return (1);
	return (0);
}

int		ft_isoperator(char *s, int len)
{
	if (!ft_strncmp(s, LTLT, len))
		return (ltlt);
	if (!ft_strncmp(s, GTGT, len))
		return (gtgt);
	if (!ft_strncmp(s, LT, len))
		return (lt);
	if (!ft_strncmp(s, GT, len))
		return (gt);
	if (!ft_strncmp(s, OR, len))
		return (or);
	if (!ft_strncmp(s, PIPE, len))
		return (pip);
	if (!ft_strncmp(s, AND, len))
		return (and);
	if (!ft_strncmp(s, LBR, len))
		return (lbr);
	if (!ft_strncmp(s, RBR, len))
		return (rbr);
	return (-1);
}

char	*meta(char *read_line, int *nt)
{
	int 	next_token;

	next_token = 0;
	while (read_line[next_token] && \
			ft_ismeta(read_line[next_token]) && \
			ft_isoperator(read_line, next_token + 1) != -1)
		next_token++;
	if (nt)
		*nt = next_token;
	return (read_line + next_token);
}

int		quoting(char *read_line)
{
	char quote;
	char *res;

	quote = *read_line;
	res = ft_strchr(read_line + 1, quote);
	if (!res)
		return (1);
	return (res - read_line + 1);
}

char	*word(char *read_line, int *nt)
{
	int		next_token;

	next_token = 0;
	while (read_line[next_token] && \
			!ft_ismeta(read_line[next_token]) && \
			!ft_isspace(read_line[next_token]))
	{
		if (read_line[next_token] == '\'' || \
			read_line[next_token] == '\"')
			next_token += quoting(read_line + next_token);
		next_token++;
	}
	if (nt)
		*nt = next_token;
	return (read_line + next_token);
}

char	*oper_token(char *read_line, int *len)
{
	while (ft_isspace(*read_line))
		read_line++;
	if (ft_ismeta(*read_line))
		return (meta(read_line, len));
	return (word(read_line, len));
}

size_t get_number(char *read_line)
{
	int	num;

	num = 0;
	while (*read_line)
	{
		read_line = oper_token(read_line, NULL);
		num++;
	}
	return (num);
}

char *get_token(char **read_line)
{
	int 	len;

	*read_line = oper_token(*read_line, &len);
	return (ft_substr(*read_line - len, 0, len));
}

char **get_tokens(char *read_line)
{
	size_t	num;
	char 	**tokens;
	int		i;

	num = get_number(read_line);
	tokens = malloc(sizeof(char *) * (num + 1));
	if (!tokens)
		return (NULL);
	tokens[num] = NULL;
	i = 0;
	while (*read_line)
	{
		tokens[i] = get_token(&read_line);
		i++;
	}
	return (tokens);
}

// int main(int argc, char *argv[])
/*{
	char **tokens;

	if (argc != 2)
		return (1);
	tokens = get_tokens(argv[1]);
	while (*tokens)
	{
		printf("%p %s\n", tokens, *tokens);
		tokens++;
	}
	return (0);
}
*/