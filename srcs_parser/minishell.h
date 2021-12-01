#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H
# include "libft.h"
# include <stdio.h>

# define LTLT "<<"
# define GTGT ">>"
# define LT "<"
# define GT ">"
# define OR "||"
# define PIPE "|"
# define AND "&&"
# define LBR "("
# define RBR ")"
enum e_operators {
	ltlt,
	gtgt,
	lt,
	gt,
	or,
	pip,
	and,
	lbr,
	rbr
};

int		ft_isoperator(char *s, int len);

#endif
