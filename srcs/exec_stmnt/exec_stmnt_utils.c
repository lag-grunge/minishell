#include "minishell.h"
#include "exec_stmnt.h"
#include "redirect.h"
#include "environment.h"

void save_restore_stdin_stdount(void)
{
	static int sav_in;
	static int sav_out;

	if (sav_in > 0 || sav_out > 0)
	{
		dup2(sav_in, STDIN_FILENO);
		close(sav_in);
		dup2(sav_out, STDOUT_FILENO);
		close(sav_out);
		sav_in = 0;
		sav_out = 0;
	}
	else
	{
		sav_in = dup(STDIN_FILENO);
		sav_out = dup(STDOUT_FILENO);
	}
}

static int wait_pipe(int *p)
{
	int	status;
	save_restore_stdin_stdount();
	(*p)++;
	while (*p)
	{
		waitpid(0, &status, 0);
		(*p)--;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (0);
}

static int wait_child(pid_t pid)
{
	int status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (0);
}

static void exec_cmd(t_cmd *cmd)
{
	char	*exec_path;
	char	**env;
	int 	ret;

	ret = ft_which(&exec_path, cmd->args[0]);
	if (ret == not_fnd_bin_in_path || ret == nopath_in_env)
		exit (not_found_bin);
	else if (ret == not_perms_for_exec)
		exit (perm_den_bin);
	env = get_env_array(g_data.env);
	ret = ft_openfiles(cmd->redir, cmd->args[0]);
	if (ret)
		exit(1);
	execve(exec_path, cmd->args, env);
	perror(exec_path);
}

static int child(t_stmnt *stmnt, int h_doc[2], int pdes[2])
{
	if (stmnt->h_doc)
		ft_redirect(h_doc, STDIN_FILENO);
	if (stmnt->next_stmnt)
		ft_redirect(pdes, STDOUT_FILENO);
	if (stmnt->type == op_smpl)
		exec_cmd(stmnt->oper1);
	return (exec_stmnt(stmnt->oper1, 0));
}

int exec_smpl_sbsh(t_stmnt *stmnt, int p, int h_doc[2], int pdes[2])
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
		exit(fork_err);
	else if (pid == 0)
		return child(stmnt, h_doc, pdes);
	if (stmnt->h_doc)
	{
		ft_redirect(h_doc, STDOUT_FILENO);
//			read_here_doc();
	}
	if (stmnt->next_stmnt)
	{
			ft_redirect(pdes, STDIN_FILENO);
			return (exec_stmnt(stmnt->next_stmnt, ++p));
	}
	else if (p)
		return (wait_pipe(&p));
	return (wait_child(pid));
}