#include "exec_stmnt.h"

void	save_restore_stdin_stdount(void)
{
	static int sav_in;
	static int sav_out;
	static int sav_err;

	if (!isatty(STDIN_FILENO))
	{
		dup2(sav_in, STDIN_FILENO);
		close(sav_in);
		dup2(sav_out, STDOUT_FILENO);
		close(sav_out);
		dup2(sav_err, STDERR_FILENO);
		close(sav_err);
	}
	else
	{
		sav_in = dup(STDIN_FILENO);
		sav_out = dup(STDOUT_FILENO);
		sav_err = dup(STDERR_FILENO);
	}
}

static int get_status(int status)
{
    int     prev_code;
	int		code;
	char	*new_value;

	code = 0;
	if (WIFEXITED(status))
		code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		code = 128 + WTERMSIG(status);
    prev_code = get_last_status();
	if (prev_code != code)
	{
		new_value = ft_itoa(code);
		if (!new_value)
			exit(malloc_err);
		set_value(&g_data.env, "last_status", new_value);
	}
	return (code);
}

int	wait_child(int p)
{
	int	status;

	p++;
	while (p)
	{
		waitpid(-1, &status, 0);
		p--;
	}
	return (get_status(status));
}

int exec_bin(t_cmd *cmd)
{
	char	**env;
	char 	**args;
	char	*exec_path;
	int		ret;

	ret = ft_which(&exec_path, cmd->args->content);
	if (ret == not_fnd_bin_in_path || ret == nopath_in_env || ret == 1)
	{
		if (ret == 1)
			exit_no_file_error(not_found_bin, "");
		exit_no_file_error(not_found_bin, cmd->args->content);
	}
	else if (ret == not_perms_for_exec) {
		exit_no_perms_error(perm_den_bin, cmd->args->content);
	}
	if (!ft_strncmp(cmd->args->content, "./minishell", 12)) /////////////////////  absolute_or_another_path
		increment_shell_level();
	env = get_env_array(g_data.env);
	args = get_cmd_array(cmd->args);
	execve(exec_path, args, env);
	perror(exec_path);
	return (child_exec_err);
}

void exec_cmd(t_cmd *cmd, int *res_if_single_builtin)
{
	int 	ret;

	ret = make_all_red_exp(cmd->redir) || ft_openfiles(cmd->redir);
	if (ret)
		exit(1);
	if (!cmd->args)
		exit (0);
	make_expansions(&cmd->args);
	if (cmd->args && !ft_is_bilt(cmd->args))
		ret = exec_bin(cmd);
	else if (cmd->args)
	{
		ret = ft_bilt_start(cmd->args, &g_data);
		if (res_if_single_builtin)
		{
			*res_if_single_builtin = ret;
			return;
		}
	}
	exit(ret);
}
