#ifndef MINISHELL_H
#define MINISHELL_H
# include "libft.h"
# include <dirent.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>

typedef enum e_errors {
	syntax_err = 2,
	malloc_err = 3,
	file_err = 4,
	fork_err = 5
}				t_returns;

# define LTLT "<<"
# define GTGT ">>"
# define LT "<"
# define GT ">"
# define OR "||"
# define PIPE "|"
# define AND "&&"
# define LBR "("
# define RBR ")"
# define MAX_CTRLS_LEN 2

typedef enum e_ctrls {
	ct_ltlt,
	ct_gtgt,
	ct_lt,
	ct_gt,
	ct_or,
	ct_pip,
	ct_and,
	ct_lbr,
	ct_rbr
} t_ctrls;

typedef enum e_token {
	lg,
	wrd,
	op,
	pp,
	lb,
	rb
} t_token;

typedef enum e_tstmnt {
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
	t_tred	type;
	char	*word;
	struct	s_redir *next;
}			t_redir;

typedef struct s_cmd {
	char 			**args;
	t_redir 		*redir;
}			t_cmd;

typedef struct s_stmnt {
	int 			type;
	void			*oper1;
	void			*oper2;
	pid_t			pid1;
	pid_t			pid2;
	t_redir			*redir; //	common redir for subshell
	struct s_stmnt 	*next_stmnt; // pipe
}			t_stmnt;

typedef struct s_env {
	char *key;
	char sep;
	char *value;
	struct s_env *next;
} 				t_env;

typedef struct s_data {
	t_env	*env;
	int 	last_status;

}				t_data;

t_data g_data;

#endif
