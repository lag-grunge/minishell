/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_stmnt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 01:19:52 by sdalton           #+#    #+#             */
/*   Updated: 2022/03/18 21:49:33 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "exec_stmnt.h"
#include "signal_dispose.h"
#include "redirect.h"

static void	ft_child(t_stmnt *stmnt, int pdes[2])
{
	int	ret;

	signal_dispose(child_fork);
	if (stmnt->next_stmnt)
		ft_redirect(pdes, STDOUT_FILENO);
	if (stmnt->type == op_smpl)
		exec_cmd(stmnt->oper1, 0);
	else if (stmnt->type == op_sbsh)
	{
		ret = make_all_red_exp(stmnt->redir);
		if (!ret)
			ret = ft_openfiles(stmnt->redir);
		if (ret)
			exit(1);
		exec_stmnt(stmnt->oper1, 0);
		exit(g_data.last_stat);
	}
}

static void	ft_parent(t_stmnt *stmnt, int pdes[2], int p)
{
	signal_dispose(parent_fork);
	if (stmnt->next_stmnt)
	{
		ft_redirect(pdes, STDIN_FILENO);
		exec_stmnt(stmnt->next_stmnt, ++p);
	}
	else
	{
		if (p >= 1)
			save_restore_stdin_stdount();
		wait_child(p, stmnt->pid);
		signal_dispose(main_shell);
	}
}

int	ft_is_single_bilt(t_stmnt *stmnt, int p)
{
	if (stmnt->type == op_sbsh)
		return (0);
	if (p || stmnt->next_stmnt)
		return (0);
	if (!((t_cmd *)stmnt->oper1)->args)
		return (0);
	return (ft_is_bilt(((t_cmd *)stmnt->oper1)->args));
}

void	exec_smpl_sbsh(t_stmnt *stmnt, int p, int pdes[2])
{
	pid_t	pid;

	if (stmnt->next_stmnt && pipe(pdes) == -1)
		exit (fork_err);
	if ((stmnt->next_stmnt && !p) || ft_is_single_bilt(stmnt, p))
		save_restore_stdin_stdount();
	if (ft_is_single_bilt(stmnt, p))
	{
		exec_cmd(stmnt->oper1, 1);
		save_restore_stdin_stdount();
		return ;
	}
	pid = fork();
	if (pid < 0)
		exit(fork_err);
	else if (pid == 0)
		ft_child(stmnt, pdes);
	else
	{
		stmnt->pid = pid;
		ft_parent(stmnt, pdes, p);
	}
}

void	exec_stmnt(t_stmnt *stmnt, int p)
{
	int	pdes[2];

	if (stmnt->type == op_smpl || stmnt->type == op_sbsh)
		exec_smpl_sbsh(stmnt, p, pdes);
	else if (stmnt->type == op_or || stmnt->type == op_and)
	{
		exec_stmnt(stmnt->oper1, 0);
		if ((!g_data.last_stat && stmnt->type == op_and) || \
			(g_data.last_stat && stmnt->type == op_or))
			exec_stmnt(stmnt->oper2, 0);
	}
}
