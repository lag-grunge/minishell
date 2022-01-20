#include "expansions.h"
#include "syntax.h"

static int get_size(char *token)
{
	int	size;
	int qlen;

	size = 0;
	while (*token)
	{
		if (*token == '\'' || *token == '\"')
		{
			qlen = quoting(token);
			size += qlen - 2;
			token += qlen;
			continue ;
		}
		token++;
		size++;
	}
	return (size);
}

/* 'a" b"c' -> 'a bc' */
//void quote_removal(char **token)
char  *quote_removal(char *token)
{
	int new_len;
	int	i;
	char	*new_token;
	int qlen;

	new_len = get_size(token);
	new_token = ft_calloc(new_len + 1, sizeof(char));
	i = 0;
	while (*token)
	{
		if (*token == '\'' || *token == '\"')
		{
			qlen = quoting(token);
			ft_strlcat(new_token, token + 1, i + qlen - 2 + 1);
			(token) += qlen;
			i += qlen - 2;
			continue ;
		}
		new_token[i] = *token;
		(token)++;
		i++;
	}
	return (new_token);
}

//int main()
//{
//	printf("%s\n%s\n\n", "\"*\"", quote_removal("\"*\""));
//	printf("%s\n%s\n\n", "\"*.c\"", quote_removal("\"*.c\""));
//	printf("%s\n%s\n\n", "\"*\'.c\"", quote_removal("\"*\'.c\""));
//	printf("%s\n%s\n\n", "\"*\'.c\"", quote_removal("\"*\'.c\""));
//	printf("%s\n%s\n\n", "\"*\'.\'c\"", quote_removal("\"*\'.\'c\""));
//
//	printf("%s\n%s\n\n", "*.c\"*\"", quote_removal("*.c\"*\""));
//	printf("%s\n%s\n\n", "\"*\"*.c", quote_removal("\"*\"*.c"));
//	printf("%s\n%s\n\n", "*\"*\".c", quote_removal("*\"*\".c"));
//	printf("%s\n%s\n\n", "*.c", quote_removal("*.c"));
//}