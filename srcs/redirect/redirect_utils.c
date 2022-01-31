#include "minishell.h"

static char	*str_err(const char *filename, const char *cmd_name)
{
	char	*tmp_err;
	int 	err_len;
	int 	cmd_len;

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

int		print_err(char *filename, char *cmd_name)
{
	char *tmp;

	tmp = str_err(filename, cmd_name);
	if (!tmp)
		exit(malloc_err);
	perror(tmp);
	free(tmp);
	return (-file_err);
}

