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

int ft_isoperator(char *s)
{
	if (!ft_strncmp(s, LTLT, MAX_CTRLS_LEN))
		return (ct_ltlt);
	if (!ft_strncmp(s, GTGT, MAX_CTRLS_LEN))
		return (ct_gtgt);
	if (!ft_strncmp(s, LT, MAX_CTRLS_LEN))
		return (ct_lt);
	if (!ft_strncmp(s, GT, MAX_CTRLS_LEN))
		return (ct_gt);
	if (!ft_strncmp(s, OR, MAX_CTRLS_LEN))
		return (ct_or);
	if (!ft_strncmp(s, PIPE, MAX_CTRLS_LEN))
		return (ct_pip);
	if (!ft_strncmp(s, AND, MAX_CTRLS_LEN))
		return (ct_and);
	if (!ft_strncmp(s, LBR, MAX_CTRLS_LEN))
		return (ct_lbr);
	if (!ft_strncmp(s, RBR, MAX_CTRLS_LEN))
		return (ct_rbr);
	return (-1);
}

char	*meta(char *read_line, int *nt)
{
	int 	next_token;
	char	*tmp;


	tmp = ft_substr(read_line, 0, MAX_CTRLS_LEN);
	next_token = MAX_CTRLS_LEN;
	while (ft_isoperator(tmp) == -1)
	{
		next_token--;
		free(tmp);
		tmp = ft_substr(read_line, 0, next_token);
	}
	if (nt)
		*nt = next_token;
	return (read_line + next_token);
}

static int		quoting(char *read_line)
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
		else
			next_token++;
	}
	if (nt)
		*nt = next_token;
	return (read_line + next_token);
}
