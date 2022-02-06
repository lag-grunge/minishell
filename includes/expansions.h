#ifndef MINISHELL_EXPANSIONS_H
#define MINISHELL_EXPANSIONS_H
#include "minishell.h"
#include "environment.h"
#include "parser.h"
#include "syntax.h"

int variable_expansion(t_list *args);
void filename_expansion(t_list *args_list, int exp_num);
int	match(char *d_name, char *token);
char	*quote_removal(char *token);
void exec_expansion(char **token);
int make_all_red_exp(t_redir *red);
void	make_expansions(t_list **args);


#endif
