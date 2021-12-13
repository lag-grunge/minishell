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
typedef enum e_topers {
	ltlt,
	gtgt,
	lt,
	gt,
	or,
	pip,
	and,
	lbr,
	rbr
} t_topers;

typedef enum e_tstmnt {
	op_none,
	op_smpl,
	op_or,
	op_and,
	op_sbsh
} t_tstmnt;

typedef enum e_tred {
	red_rifile,
	red_rh_doc,
	red_wofile,
	red_aofile
} t_tred;

typedef struct s_redir {
	t_tred	in;
	char	*infile;
	char	*lim;
	t_tred	out;
	char	*outfile;
}			t_redir;

typedef struct s_cmd {
	char 			**args;
	t_redir 		*redir;
	struct	s_cmd 	*next_cmd; // if PIPE
}			t_cmd;

typedef struct s_stmnt {
	t_tstmnt type;
	t_tstmnt type1; // none, simple, && , || (enum and or)
	void	*oper1;
	t_tstmnt type2; //
	void	*oper2;
	t_redir	*redir; // common redir for subshell
}			t_stmnt;

#endif
