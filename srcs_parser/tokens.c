#include "minishell.h"

char	*meta(char *read_line)
{
	int 	next_token;

	next_token = 0;
	while (ft_ismeta(read_line[next_token]))
		next_token++;
	return (read_line + next_token);
}

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

int		quouting(char *read_line)
{
	char quote;
	char *res;

	quote = *read_line;
	res = ft_strchr(read_line + 1, quote);
	if (!res)
		return (1);
	return (res - read_line + 1);
}

char	*word(char *read_line)
{
	int		next_token;

	next_token = 0;
	while (!ft_ismeta(read_line[next_token]) && \
			!ft_isspace(read_line[next_token]))
	{
		if (read_line[next_token] == '\'' || \
			read_line[next_token] == '\"')
			next_token += quoting(read_line + next_token);
		next_token++;
	}
	return (read_line + next_token);
}


size_t get_number(char *read_line, char **new)
{
	int	num;

	num = 0;
	while (*read_line)
	{
		while (ft_isspace(*read_line))
			read_line++;
		if (ft_ismeta(*read_line))
			read_line =	meta(read_line);
		else
			read_line = word(read_line);
		num++;
	}
	return (num);
}

char *get_token(char **read_line)
{
	char	*line;

	line = *read_line;
	if (*line == )


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

int main(int argc, char *argv[])
{
	char **tokens;

	if (argc != 2)
		return (1);
	tokens = get_tokens(argv[1]);
	while (tokens)
	{
		printf("%s\n", *tokens);
		tokens++;
	}
	return (0);
}
