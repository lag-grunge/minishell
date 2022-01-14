#ifndef MINISHELL_ENVIRONMENT_H
#define MINISHELL_ENVIRONMENT_H
#include "minishell.h"

int 	get_env_hash(t_env **env_start, char *env[]);
char	*get_key_value(t_env *env, char *key);

#endif
