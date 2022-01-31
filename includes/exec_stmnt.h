#ifndef MINISHELL_EXEC_STMNT_H
#define MINISHELL_EXEC_STMNT_H

enum e_err	{
	nopath_in_env = 2,
	not_perms_for_exec = 3,
	not_fnd_bin_in_path = 4,
};

void exec_stmnt(t_stmnt *stmnt, int *res, int p);
int	ft_which(char **exec_path, char *cmd);

//int wait_child(pid_t pid);
//int wait_pipe(int *p);
void save_restore_stdin_stdount(void);
//int exec_stmnt_or_and(t_stmnt *stmnt);
int exec_smpl_sbsh(t_stmnt *stmnt, int p, int pdes[2]);

#endif
