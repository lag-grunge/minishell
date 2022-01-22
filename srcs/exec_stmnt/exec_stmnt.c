#include "../includes/minishell.h"
#include "exec_stmnt.h"
#include "environment.h"
#include "redirect.h"

static int exec_cmd(t_cmd *cmd)
{
	char	*exec_path;
	char	**env;

	ft_which(&exec_path, cmd->args[0]);
	env = get_env_array(g_data.env);
	ft_openfiles(cmd->redir);
	execve(exec_path, cmd->args, env);
	perror(exec_path);
}

int exec_stmnt(t_stmnt *stmnt)
{
	pid_t pid;
	int pdes[2];
	int status;
	static int p;
	int ret;

	if (stmnt->next_stmnt && pipe(pdes) == -1)
		exit (fork_err);
	if (stmnt->type == op_smpl || stmnt->type == op_sbsh)
	{
		pid = fork();
		if (pid == 0)
		{
			if (stmnt->next_stmnt)
				ft_redirect(pdes, STDOUT_FILENO);
			if (stmnt->type == op_smpl)
				exec_cmd(stmnt->oper1);
			else if (stmnt->type == op_sbsh)
				return (exec_stmnt(stmnt->oper1));
		}
		else if (pid > 0)
		{
			if (stmnt->next_stmnt)
			{
				ft_redirect(pdes, STDIN_FILENO);
				p++;
				exec_stmnt(stmnt->next_stmnt);
			}
			else if (p)
			{
				p++;
				while (p)
				{
					waitpid(0, &status, 0);
					p--;
				}
				if (WIFEXITED(status))
					return (WEXITSTATUS(status));
				else if (WIFSIGNALED(status))
					return (WTERMSIG(status));
			}
			else
			{
				waitpid(pid, &status, 0);
				if (WIFEXITED(status))
					return (WEXITSTATUS(status));
				else if (WIFSIGNALED(status))
					return (WTERMSIG(status));
			}
		}
		else if (pid < 0)
			exit(fork_err);
	}
	else if (stmnt->type == op_or || stmnt->type == op_and)
	{
		ret = exec_stmnt(stmnt->oper1);
		if ((!ret && stmnt->type == op_and) || (ret && stmnt->type == op_or))
			ret = exec_stmnt(stmnt->oper2);
		return (ret);
	}
}
//	if (stmnt->next_stmnt && pipe(pdes) == -1)
//		exit (fork_err);
//	pid = fork();
//	if (pid == 0)
//	{
//		if (stmnt->next_stmnt)
//			ft_redirect(pdes, STDOUT_FILENO);
//		if (stmnt->type == op_smpl)
//			exec_cmd(stmnt->oper1);
//		else
//			exec_stmnt(stmnt->oper1);
//	}
//	else if (pid > 0)
//	{
//		if (st_pid)
//			*st_pid = pid;
//		else
//			stmnt->pid1 = pid;
//		if (stmnt->next_stmnt)
//		{
//			ft_redirect(pdes, STDIN_FILENO);
//			p++;
//			exec_stmnt(stmnt->next_stmnt);
//		}
//		if (p)
//		{
//			while (p + 1)
//			{
//				waitpid(0, &status, 0);
//				p--;
//			}
//			p = 0;
//		}
//		else if (!st_pid)
//			waitpid(stmnt->pid1, &status, 0);
//		else
//			waitpid(*st_pid, &status, 0);
//		g_data.last_status = WEXITSTATUS(status);
//		if ((stmnt->type == op_or && WEXITSTATUS(status) > 0) \
//			|| (stmnt->type == op_and && WEXITSTATUS(status) == 0))
//			exec_stmnt(stmnt->oper2);
//	}
//}