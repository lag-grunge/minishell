#include "minishell.h"
#include "clean.h"

int exit_shell(void)
{
//	clean_env_hash(g_data.env);
//	printf("\033[1A");
//	printf("\033[10C ");
	printf(" exit\n");
	exit(0);
}