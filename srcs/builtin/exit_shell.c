#include "minishell.h"
#include "clean.h"

int exit_shell(void)
{
	clean_env_hash(g_data.env);
    	ft_putstr_fd("\033[Aminishell> exit\n", STDERR_FILENO);
	exit(0);
}
