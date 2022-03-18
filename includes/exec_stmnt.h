#ifndef EXEC_STMNT_H
# define EXEC_STMNT_H
# include "minishell.h"
# include "redirect.h"
# include "environment.h"
# include "expansions.h"
# include "error.h"
# include "biltins.h"

enum e_err	{
	nopath_in_env = 2,
	not_perms_for_exec = 3,
	not_fnd_bin_in_path = 4,
};

void exec_stmnt(t_stmnt *stmnt, int p);
int	ft_which(char **exec_path, char *cmd);
void exec_smpl_sbsh(t_stmnt *stmnt, int p, int pdes[2]);
int wait_child(int p, pid_t pid);
void exec_cmd(t_cmd *cmd, int sng_blt);
char	**get_cmd_array(t_list *args_list);

#endif
