#ifndef MINISHELL_EXPANSIONS_H
#define MINISHELL_EXPANSIONS_H
#include "minishell.h"

char ** variable_expansion(char **token, t_env *env);
int filename_expansion(char **filenames, char *pwd, char **spl_token);
int	match(char *d_name, char *token);
int	count_filename_expansion(char *pwd, char **spl_token);
char	*quote_removal(char *token);

#endif
