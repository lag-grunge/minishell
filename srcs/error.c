#include "minishell.h"
#include "error.h"

int syntax_error(int ret, char *token, char *module)
{
	if (module)
		ft_putstr_fd(module, STDERR_FILENO);
	if (token)
	{
		ft_putstr_fd(" :unexpected token ", STDERR_FILENO);
		if (token) {
			ft_putchar_fd('\'',STDERR_FILENO);
			ft_putstr_fd(token, STDERR_FILENO);
			ft_putchar_fd('\'',STDERR_FILENO);
		}
	}
	ft_putchar_fd('\n',STDERR_FILENO);
	return (ret);
}

int	exit_no_file_error(int ret, char *filename)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory!", STDERR_FILENO);
	exit(ret);
}

int exit_no_perms_error(int ret, char *filename)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putendl_fd(": Permission denied!", STDERR_FILENO);
	exit(ret);
}
