#include "minishell.h"

static char	*str_err(const char *filename, const char *cmd_name)
{
	char	*tmp_err;
	int		err_len;
	int		cmd_len;

	cmd_len = (int)ft_strlen(cmd_name);
	err_len = (int)ft_strlen(filename);
	err_len += cmd_len + 1;
	tmp_err = (char *) malloc(sizeof(char) * (err_len + 1));
	if (!tmp_err)
		return (NULL);
	ft_strlcpy(tmp_err, cmd_name, cmd_len + 1);
	tmp_err[cmd_len] = ':';
	tmp_err[cmd_len + 1] = 0;
	ft_strlcat(tmp_err, filename, err_len + 1);
	return (tmp_err);
}

int	print_err(char *filename, char *cmd_name)
{
	char	*tmp;

	tmp = str_err(filename, cmd_name);
	if (!tmp)
		exit(malloc_err);
	perror(tmp);
	free(tmp);
	return (-file_err);
}

int	open_for_read(char *filename, int fd_in)
{
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	fd_in = open(filename, O_RDONLY);
	if (fd_in == -1)
		return (print_err(filename, "./minishell"));
	return (fd_in);
}

int	open_for_write(char *filename, int fd_out, int append, int err)
{
	if ((!err && fd_out != STDOUT_FILENO) || (err && fd_out != STDERR_FILENO))
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

void	save_restore_stdin_stdount(void)
{
	static int	sav_in = STDIN_FILENO;
	static int	sav_out = STDOUT_FILENO;
	static int	sav_err = STDERR_FILENO;

	if (STDOUT_FILENO != sav_out || STDIN_FILENO != sav_in
		|| STDERR_FILENO != sav_err)
	{
		dup2(sav_in, STDIN_FILENO);
		close(sav_in);
		sav_in = STDIN_FILENO;
		dup2(sav_out, STDOUT_FILENO);
		close(sav_out);
		sav_out = STDOUT_FILENO;
		dup2(sav_err, STDERR_FILENO);
		close(sav_err);
		sav_err = STDERR_FILENO;
	}
	else
	{
		sav_in = dup(STDIN_FILENO);
		sav_out = dup(STDOUT_FILENO);
		sav_err = dup(STDERR_FILENO);
	}
}
