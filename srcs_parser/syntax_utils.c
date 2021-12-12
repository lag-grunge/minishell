#include "syntax.h"

t_token	type(char *cur)
{
	int ret;

	ret = ft_isoperator(cur, ft_strlen(cur));
	if (ret >= ltlt && ret <= gt)
		return (lg);
	else if (ret == or || ret == and)
		return (op);
	else if (ret == pip)
		return (pp);
	else if (ret == lbr)
		return (lb);
	else if (ret == rbr)
		return (rb);
	else
		return (wrd);
}

int expect(t_token t, char ***cur)
{
	if (accept(t, cur))
		return (1);
	return (error());
}

int	error(void)
{
	printf("unexpected t_token\n");
	return (0);
}

char **nextsym(char **cur)
{
	return (cur + 1);
}

int accept(t_token t, char ***cur)
{
	if (t == type(**cur))
	{
		*cur = nextsym(*cur);
		return (1);
	}
	return (0);
}

