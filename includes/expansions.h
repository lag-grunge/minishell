#ifndef MINISHELL_EXPANSIONS_H
#define MINISHELL_EXPANSIONS_H
#include "minishell.h"
#include "environment.h"
#include "parser.h"
#include "syntax.h"

void variable_expansion(t_list *args_list);
void filename_expansion(t_list *args_list);
int	match(char *d_name, char *token);
void exec_expansion(char **token);
int make_all_red_exp(t_redir *red);
void	make_expansions(t_list **args);


#endif
