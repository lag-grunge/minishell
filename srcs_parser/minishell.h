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

enum e_opers {
	op_none,
	op_smpl,
	op_or,
	op_and,
	op_sbsh
};

typedef 	s_redir {
	char	in;
	char	*file1;
	char	out;
	char	*file2;
}			t_redir;

typedef 	s_cmd {
	char			*cmd;
	char 			*args;
	t_redir 		*redir;
	struct	s_cmd 	*next_cmd; // if PIPE
}			t_cmd;

typedef 	s_opers {
	char 	type1; // none, simple, && , ||, subshell (enum and or)
	void	*oper1;
	char	type2; //
	void	*oper2;
}			t_opers;

/* tokens */
int		ft_isoperator(char *s, int len);

/* opers */
t_opers *ft_oper_new(void);
t_cmd	*ft_cmd_new(void);

/* clean */
void	clean_opers(t_opers *opers);


#endif
