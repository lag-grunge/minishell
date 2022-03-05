#include "../../includes/syntax.h"

t_token	type(char *cur)
{
	int ret;

	ret = ft_isoperator(cur);
	if (ret >= ct_ltlt && ret <= ct_egtgt)
		return (lg);
	else if (ret == ct_or || ret == ct_and)
		return (op);
	else if (ret == ct_pip)
		return (pp);
	else if (ret == ct_lbr)
		return (lb);
	else if (ret == ct_rbr)
		return (rb);
	else
		return (wrd);
}

int expect(t_token t, char ***cur, char *module)
{
	if (accept(t, cur))
		return (0);
	return (syntax_error(syntax_err, **cur, module));
}

char *ft_name(char *start)
{
	if (!ft_isalpha(*start) && *start != '_')
		return (start);
	while (ft_isalnum(*start) || *start == '_')
		start++;
	return (start);
}



int syntax_error(int ret, char *token, char *module)
{
	if (module)
//		printf("%s", module);
		ft_putstr_fd(module, STDERR_FILENO);
	if (token)
	{
//		printf(" :unexpected token ");
		ft_putstr_fd(" :unexpected token ", STDERR_FILENO);
		if (token) {
//			printf("'%s'", token);
			ft_putchar_fd('\'',STDERR_FILENO);
			ft_putstr_fd(token, STDERR_FILENO);
			ft_putchar_fd('\'',STDERR_FILENO);
		}
	}
//	printf("\n");
	ft_putchar_fd('\n',STDERR_FILENO);
	return (ret);
}

int accept(t_token t, char ***cur)
{
	if (**cur && t == type(**cur))
	{
		*cur += 1;
		return (1);
	}
	return (0);
}

