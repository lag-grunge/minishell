#include "minishell.h"

int ft_ok_brackets(char *op1, char *tokens[]) {
	int br;

	if (op1)
	{
		ret = ft_is_operator(b, ft_strlen(*tokens));
		if (ret < pip || ret > and)
			return (1);
		return (0);
	}
	br = 1;
	while (*tokens) {
		if (!ft_strncmp(LBR, *tokens, 2))
			br++;
		else if (!ft_strncmp(RBR, *tokens, 2))
			br--;
		if (br < 0)
			return (0);
		tokens++;
	}
	if (br)
		return (0);
	return (1);
}

int ft_ok_opers(char *a, char *b)
{
	int ret;

	if (!a || !b)
		return (0);
	ret = ft_is_operator(b, ft_strlen(*tokens));
	if (ret != -1)
		return (0);
	return (1);
}

int ft_ok_redir(char *b)
{
	int ret;

	if (!b)
		return (0);
	ret = ft_is_operator(b, ft_strlen(*tokens));
	if (ret != -1)
		return (0);
	return (1);
}

int ft_ok_gramm(char *tokens[]) {
	int ret;
	int o;
	char *op1;
	char *op2;

	ret = 1;
	op1 = NULL;
	while (*tokens && ret) {
		ret = ft_is_operator(*tokens, ft_strlen(*tokens));
		if (ret >= ltlt && ret <= gt)
			ret = ft_ok_redir(tokens [1]);
		else if (ret >= pip && ret <= or)
		{
			op2 = tokens[1];
			ret = ft_ok_opers(op1, op2);
		}
		else if (ret >= lbr && ret <= rbr)
		{
			ft_ok_brackets(op1, tokens + 1);
		}
		else
			op1 = *tokens;
		tokens++;
	}

}