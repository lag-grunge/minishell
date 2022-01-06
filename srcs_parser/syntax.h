#ifndef MINISHELL_SYNTAX_H
#define MINISHELL_SYNTAX_H
#include "minishell.h"

t_token	type(char *cur);
int expect(t_token t, char ***cur, char *module);
int expect2(t_token t, t_token t2, char ***cur, char *module);

int syntax_error(int ret, char *token, char *module);
int accept(t_token t, char ***cur);


char **get_tokens(char *read_line, int *empty);
char *meta(char *read_line, int *nt, char **unexp);
char	*word(char *read_line, int *nt);
int		ft_ismeta(int c);
int 	ft_isoperator(char *s);

#endif
