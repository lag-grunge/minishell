#ifndef MINISHELL_ENVIRONMENT_H
#define MINISHELL_ENVIRONMENT_H
#include "minishell.h"

int 	get_env_hash(t_env **env_start, char *env[]);
char	*get_value(t_env *env, char *key);
char	**get_env_array(t_env *env_hash);
int	increment_shell_level(void);
t_env *ft_env_new_elem(void);
int write_key_value_to_elem(t_env *cur, char *cur_env, int start);
int set_value(t_env **env, char *key, char *value, int new);

#endif
