#include "minishell.h"
#include "clean.h"

int exit_shell(void)
{
	clean_env_hash(g_data.env);
	printf(" exit\n");
	exit(0);
}