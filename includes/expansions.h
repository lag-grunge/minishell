#ifndef MINISHELL_EXPANSIONS_H
#define MINISHELL_EXPANSIONS_H
#include "minishell.h"

void	variable_expansion(char **tokens, t_env *env);
char	**filename_expansion(char *pwd, char *token, int *empty);

#endif
