/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_stmnt_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 00:14:04 by sdalton           #+#    #+#             */
/*   Updated: 2022/03/18 00:29:02 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_stmnt.h"

static int	get_status(int status)
{
	int		code;

	code = 0;
	if (WIFEXITED(status))
		code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		code = 128 + WTERMSIG(status);
	return (code);
}

int	wait_child(int p, pid_t pid_last)
{
	int		status;
	pid_t	pid;
	int		ret;

	p++;
	ret = 0;
	while (p)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == pid_last)
		{
			ret = get_status(status);
			g_data.last_stat = ret;
		}
		p--;
	}
	return (ret);
}

static int	exec_bin(t_cmd *cmd)
{
	char	**env;
	char	**args;
	char	*exec_path;
	int		ret;

	ret = ft_which(&exec_path, cmd->args->content);
	if (ret == not_fnd_bin_in_path || ret == nopath_in_env || ret == 1)
	{
		if (ret == 1)
			exit_no_file_error(not_found_bin, "");
		exit_no_file_error(not_found_bin, cmd->args->content);
	}
	else if (ret == not_perms_for_exec)
		exit_no_perms_error(perm_den_bin, cmd->args->content);
	env = get_env_array(g_data.env);
	args = get_cmd_array(cmd->args);
	execve(exec_path, args, env);
	perror(exec_path);
	return (not_found_bin);
}


void exec_cmd(t_cmd *cmd, int sng_blt)
{
	int	ret;

	ret = make_all_red_exp(cmd->redir);
	if (!ret)
		ret = ft_openfiles(cmd->redir);
	if (!sng_blt && ret)
		exit(1);
	if ((!sng_blt && !cmd->args) || !ft_strncmp(cmd->args->content, "true", 5))
		exit (0);
	else if (!sng_blt && !ft_strncmp(cmd->args->content, "false", 6))
		exit (1);
	else if (sng_blt && ret)
		g_data.last_stat = 1;
	if (!ret)
		make_expansions(&cmd->args);
	if (!ret && cmd->args && !ft_is_bilt(cmd->args))
		ret = exec_bin(cmd);
	else if (!ret && cmd->args)
		ret = ft_bilt_start(cmd->args);
	if (sng_blt)
		g_data.last_stat = ret;
	if (sng_blt)
		return;
	exit(ret);
}
