#include "minishell.h"
#include "redirect.h"

int open_for_read(char *filename, char *cmd_name)
{
	int	fd_in;

	fd_in = open(filename, O_RDONLY);
	if (fd_in == -1)
		return (print_err(filename, cmd_name));
	return (fd_in);
}

int open_for_write(char *filename, int append, char *cmd_name)
{
	int	fd_out;

	fd_out = open(filename, O_WRONLY | O_CREAT | O_EXCL, 0666);
	if (fd_out == -1)
	{
		if (errno != EEXIST)
			return (print_err(filename, cmd_name));
		if (append)
			fd_out = open(filename, O_WRONLY | O_APPEND);
		else
			fd_out = open(filename, O_WRONLY | O_TRUNC);
		if (fd_out == -1)
			return (print_err(filename, cmd_name));
	}
	return (fd_out);
}

int ft_openfiles(t_redir *red, char *cmd_name)
{
	int	fd_in;
	int fd_out;

	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	while (red)
	{
		if (red->type == red_rifile)
			fd_in = open_for_read(red->word, cmd_name);
		else if (red->type == red_wofile || red->type == red_aofile)
			fd_out = open_for_write(red->word, red->type == red_aofile, cmd_name);
		if (fd_in < 0 || fd_out < 0)
			return (file_err);
		red = red->next;
	}
	if (fd_in != STDIN_FILENO)
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