#ifndef MINISHELL_SYNTAX_H
#define MINISHELL_SYNTAX_H
#include "minishell.h"
int		ft_isoperator(char *s, int len);

t_token	type(char *cur);
int expect(t_token t, char ***cur);
char **nextsym(char **cur);
int syntax_error(int ret);
int accept(t_token t, char ***cur);

int ft_word(char **args, char ***tokens);
int ft_redir(t_redir *red, char ***tokens);
int ft_subshell(t_stmnt **stmnt, char **tokens);

#endif
