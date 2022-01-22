#ifndef MINISHELL_EXEC_STMNT_H
#define MINISHELL_EXEC_STMNT_H
#include <sys/wait.h>

enum e_err	{
	nopath_in_env = 2,
	not_perms_for_exec = 3,
	not_fnd_bin_in_path = 4,
};

int exec_stmnt(t_stmnt *stmnt);
int	ft_which(char **exec_path, char *cmd);

#endif
