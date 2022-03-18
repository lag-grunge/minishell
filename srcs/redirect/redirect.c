/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:03:54 by sdalton           #+#    #+#             */
/*   Updated: 2022/03/18 21:42:35 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"
#include "signal_dispose.h"

static int	read_in_child(const char *lim, int *h_doc)
{
	char	*line;

	signal_dispose(readln);
	switch_echoctl(0);
	while (1)
	{
		line = readline(">");
		if (!line)
			break ;
		if (!ft_strncmp(line, lim, ft_strlen(lim) + 1))
			break ;
		ft_putendl_fd(line, h_doc[1]);
		free(line);
		line = NULL;
	}
	close(h_doc[1]);
	exit (0);
}

int	read_here_doc(const char *lim, int fd_in, int *h_doc)
{
	pid_t	pid;

	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (pipe(h_doc) == -1)
		exit(fork_err);
	pid = fork();
	if (pid < 0)
		exit(fork_err);
	else if (pid == 0)
		read_in_child(lim, h_doc);
	else
		waitpid(pid, NULL, 0);
	return (h_doc[0]);
}

static void	std_redirect(int *std, int *h_doc)
{
	if (std[STDIN_FILENO] != STDIN_FILENO && std[STDIN_FILENO] == h_doc[0])
		ft_redirect(h_doc, STDIN_FILENO);
	else if (std[STDIN_FILENO] != STDIN_FILENO)
	{
		dup2(std[STDIN_FILENO], STDIN_FILENO);
		close(std[STDIN_FILENO]);
	}
	if (std[STDOUT_FILENO] != STDOUT_FILENO)
	{
		dup2(std[STDOUT_FILENO], STDOUT_FILENO);
		close(std[STDOUT_FILENO]);
	}
	if (std[STDERR_FILENO] != STDERR_FILENO)
	{
		dup2(std[STDERR_FILENO], STDERR_FILENO);
		close(std[STDERR_FILENO]);
	}
}

int	ft_openfiles(t_redir *red)
{
	int	std[3];
	int	h_doc[2];

	std[0] = 0;
	std[1] = 1;
	std[2] = 2;
	ft_memset(h_doc, 255, 2 * sizeof(int));
	while (red)
	{
		if (red->type == red_rifile)
			std[0] = open_for_read(red->word, std[0]);
		else if (red->type == red_rh_doc)
			std[0] = read_here_doc(red->word, std[0], h_doc);
		else if (red->type == red_wofile || red->type == red_aofile)
			std[1] = open_for_write(red->word, std[1], \
				red->type == red_aofile, 0);
		else if (red->type == red_eofile || red->type == red_aefile)
			std[2] = open_for_write(red->word, std[2], \
				red->type == red_aefile, 1);
		if (std[0] < 0 || std[1] < 0 || std[2] < 0)
			return (file_err);
		red = red->next;
	}
	std_redirect(std, h_doc);
	return (0);
}

void	ft_redirect(int *pdes, int in_out)
{
	if (in_out == STDIN_FILENO)
	{
		dup2(pdes[0], STDIN_FILENO);
		close(pdes[0]);
		close(pdes[1]);
	}
	else if (in_out == STDOUT_FILENO)
	{
		dup2(pdes[1], STDOUT_FILENO);
		close(pdes[0]);
		close(pdes[1]);
	}
	else if (in_out == -1)
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
	}
}
