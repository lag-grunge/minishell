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

typedef struct s_redir {
	char	in;
	char	*file1;
	char	out;
	char	*file2;
}			t_redir;

typedef struct s_cmd {
	char			*cmd;
	char 			*args;
	t_redir 		*redir;
	struct	s_cmd 	*next_cmd; // if PIPE
}			t_cmd;

typedef struct s_opers {
	char	type;
	char 	type1; // none, simple, && , ||, subshell (enum and or)
	void	*oper1;
	char	type2; //
	void	*oper2;
}			t_opers;

#endif
