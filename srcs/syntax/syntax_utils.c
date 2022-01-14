#include "../../includes/syntax.h"

t_token	type(char *cur)
{
	int ret;

	ret = ft_isoperator(cur);
	if (ret >= ct_ltlt && ret <= ct_gt)
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

int expect2(t_token t, t_token t2, char ***cur, char *module)
{
	if (accept(t, cur) || accept(t2, cur))
		return (0);
	return (syntax_error(syntax_err, **cur, module));
}


int syntax_error(int ret, char *token, char *module)
{
	if (module)
		printf("%s: ", module);
	printf("unexpected token ");
	if (token)
		printf("'%s'", token);
	printf("\n");
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
