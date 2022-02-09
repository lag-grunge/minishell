#include "exec_stmnt.h"

void	save_restore_stdin_stdount(void)
{
	static int sav_in;
	static int sav_out;

	if (!isatty(STDIN_FILENO))
	{
		dup2(sav_in, STDIN_FILENO);
		close(sav_in);
		dup2(sav_out, STDOUT_FILENO);
		close(sav_out);
	}
	else
	{
		sav_in = dup(STDIN_FILENO);
		sav_out = dup(STDOUT_FILENO);
	}
}

static int get_status(int status)
{
	int		code;
	char	*tmp;
	char	*new_value;

	code = 0;
	if (WIFEXITED(status))
		code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		code = 128 + WTERMSIG(status);
	tmp = get_value(g_data.env, "last_status");
	if (ft_atoi(tmp) != code)
	{
		new_value = ft_itoa(code);
		if (!new_value)
			exit(malloc_err);
		set_value(&g_data.env, "last_status", new_value, 0);
	}
	free(tmp);
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

void	exec_cmd(t_cmd *cmd)
{
	char	*exec_path;
	char	**env;
	char 	**args;
	int 	ret;

	ret = make_all_red_exp(cmd->redir) || ft_openfiles(cmd->redir);
	if (ret)
		exit(1);
	if (!cmd->args)
		exit (0);
	make_expansions(&cmd->args);
	if (!cmd->args)
		exit(0);
	ret = ft_which(&exec_path, cmd->args->content);
	if (ret == not_fnd_bin_in_path || ret == nopath_in_env)
		exit (not_found_bin);
	else if (ret == not_perms_for_exec)
		exit (perm_den_bin);
	if (!ft_strncmp(cmd->args->content, "./minishell", 12))
		increment_shell_level();
	env = get_env_array(g_data.env);
	args = get_cmd_array(cmd->args);
	execve(exec_path, args, env);
	perror(exec_path);
	exit(child_exec_err);
}
