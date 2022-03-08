#include "minishell.h"
#include "clean.h"
#include "environment.h"

int exit_shell(int type)
{
	char *tmp = get_value(g_data.env, "last_status");
	int ret = ft_atoi(tmp);
	free(tmp);
	clean_env_hash(g_data.env);
	if (!type)
		ft_putendl_fd("\033[Aminishell> exit", STDERR_FILENO);
	else
		ft_putendl_fd("exit", STDERR_FILENO);
	exit(ret);
//	exit(0);
}
