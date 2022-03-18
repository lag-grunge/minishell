#ifndef ERROR_H
# define ERROR_H
# include "minishell.h"

int	syntax_error(int ret, char *token, char *module);
int	exit_no_file_error(int ret, char *filename);
int	exit_no_perms_error(int ret, char *filename);
int	builtin_too_many_arguments_error(char *builtin);
int	not_valid_argument_error(char *builtin, char *argument);

#endif
