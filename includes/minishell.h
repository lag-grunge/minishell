#ifndef MINISHELL_H
#define MINISHELL_H
#ifndef TEST_G
# include "libft.h"
#else
# include "../../../libft/libft.h"
#endif
# include <dirent.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_errors {
	syntax_err = 2,
	malloc_err = 3,
	file_err = 4,
	fork_err = 5,
	child_exec_err = 6
}				t_returns;

typedef enum e_codes {
	perm_den_bin = 126,
	not_found_bin = 127
} t_codes;

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
	t_list			*args;
	t_redir 		*redir;
}			t_cmd;

typedef struct s_stmnt {
	int 			type;
	void			*oper1;
	void			*oper2;
	t_redir			*redir; //	common redir for subshell
	long 			h_doc;
	struct s_stmnt 	*next_stmnt; // pipe
}			t_stmnt;

typedef struct s_env {
	char *key;
	char sep;
	char *value;
	struct s_env *next;
} 				t_env;

enum e_child_disp {
	new_shell,
	parent_fork,
	child_fork,
	readln
};

typedef struct s_data {
	t_env	*env;
}				t_data;

#ifdef __cplusplus  //for CPP googletests
	extern t_data g_data;
#else
	t_data g_data;
#endif

#endif
