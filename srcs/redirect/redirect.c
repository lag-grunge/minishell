#include "minishell.h"
#include "redirect.h"
#include "signal_dispose.h"

int read_here_doc(const char *lim, int fd_in, int *h_doc)
{
	char	*line;
	pid_t	pid;

	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (pipe(h_doc) == -1)
		exit(fork_err);
	pid = fork();
	if (pid < 0)
		exit(fork_err);
	else if (pid == 0)
	{
		signal_dispose(readln);
		while (1)
		{
			line = readline(">");
			if (!line)
				break;
			if (!ft_strncmp(line, lim, ft_strlen(lim) + 1))
				break;
			ft_putendl_fd(line, h_doc[1]);
			free(line);
			line = NULL;
		}
		close(h_doc[1]);
		exit (0);
	}
	else
		waitpid(pid, NULL, 0);
	return (h_doc[0]);
}

int open_for_read(char *filename, int fd_in)
{
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	fd_in = open(filename, O_RDONLY);
	if (fd_in == -1)
		return (print_err(filename, "./minishell"));
	return (fd_in);
}

int open_for_write(char *filename, int fd_out, int append)
{
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	fd_out = open(filename, O_WRONLY | O_CREAT | O_EXCL, 0666);
	if (fd_out == -1)
	{
		if (errno != EEXIST)
			return (print_err(filename, "./minishell"));
		if (append)
			fd_out = open(filename, O_WRONLY | O_APPEND);
		else
			fd_out = open(filename, O_WRONLY | O_TRUNC);
		if (fd_out == -1)
			return (print_err(filename, "./minishell"));
	}
	return (fd_out);
}

int ft_openfiles(t_redir *red)
{
	int	fd_in;
	int fd_out;
	int h_doc[2];

	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	while (red)
	{
		if (red->type == red_rifile)
			fd_in = open_for_read(red->word, fd_in);
		else if (red->type == red_wofile || red->type == red_aofile)
			fd_out = open_for_write(red->word, fd_out, red->type == red_aofile);
		else if (red->type == red_rh_doc)
			fd_in = read_here_doc(red->word, fd_in, h_doc);
		if (fd_in < 0 || fd_out < 0)
			return (file_err);
		red = red->next;
	}
	if (fd_in == h_doc[0])
		ft_redirect(h_doc, STDIN_FILENO);
	else if (fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
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
		close(pdes[0]);
		close(pdes[1]);
	}
}